#include "subsystems/CommandSwerveDrivetrain.h"
#include <frc/RobotController.h>

using namespace subsystems;

// Implemented by Team 3691
// Initialize function that runs regardless of which template constructor is used
void CommandSwerveDrivetrain::DrivetrainInit(){
    frc::SmartDashboard::PutData("Swerve Widget", &m_swerveWidget);
}

void CommandSwerveDrivetrain::Periodic()
{
    /*
     * Periodically try to apply the operator perspective.
     * If we haven't applied the operator perspective before, then we should apply it regardless of DS state.
     * This allows us to correct the perspective in case the robot code restarts mid-match.
     * Otherwise, only check and apply the operator perspective if the DS is disabled.
     * This ensures driving behavior doesn't change until an explicit disable event occurs during testing.
     */
    if (!m_hasAppliedOperatorPerspective || frc::DriverStation::IsDisabled()) {
        auto const allianceColor = frc::DriverStation::GetAlliance();
        if (allianceColor) {
            SetOperatorPerspectiveForward(
                *allianceColor == frc::DriverStation::Alliance::kRed
                    ? kRedAlliancePerspectiveRotation
                    : kBlueAlliancePerspectiveRotation
            );
            m_hasAppliedOperatorPerspective = true;
        }
    }

    AddClusterVisionMeasurments();

    m_swerveWidget.Update(SwerveDrivetrain::GetState());
}

void CommandSwerveDrivetrain::StartSimThread()
{
    m_lastSimTime = utils::GetCurrentTime();
    m_simNotifier = std::make_unique<frc::Notifier>([this] {
        units::second_t const currentTime = utils::GetCurrentTime();
        auto const deltaTime = currentTime - m_lastSimTime;
        m_lastSimTime = currentTime;

        /* use the measured time delta, get battery voltage from WPILib */
        UpdateSimState(deltaTime, frc::RobotController::GetBatteryVoltage());
    });
    m_simNotifier->StartPeriodic(kSimLoopPeriod);
}

void CommandSwerveDrivetrain::ConfigurePathPlanner(){

    // Load the RobotConfig from the GUI settings. You should probably
    // store this in your Constants file
    pathplanner::RobotConfig config = pathplanner::RobotConfig::fromGUISettings();

    // Configure the AutoBuilder last
    pathplanner::AutoBuilder::configure(
        [this](){ return this->GetState().Pose; }, // Robot pose supplier
        [this](frc::Pose2d newPose){ this->ResetPose(newPose); }, // Method to reset odometry (will be called if your auto has a starting pose)
        [this](){ return this->GetState().Speeds; }, // ChassisSpeeds supplier. MUST BE ROBOT RELATIVE
                [this](frc::ChassisSpeeds const &speeds, pathplanner::DriveFeedforwards const &feedforwards) {
            return SetControl(
                m_pathApplyRobotSpeeds.WithSpeeds(speeds)
                    .WithWheelForceFeedforwardsX(feedforwards.robotRelativeForcesX)
                    .WithWheelForceFeedforwardsY(feedforwards.robotRelativeForcesY)
            );
        },
        std::make_shared<pathplanner::PPHolonomicDriveController>(
            // PID constants for translation
            pathplanner::PIDConstants{10.0, 0.0, 0.0},
            // PID constants for rotation
            pathplanner::PIDConstants{7.0, 0.0, 0.0}
        ),
        std::move(config),
        []() {
            // Boolean supplier that controls when the path will be mirrored for the red alliance
            // This will flip the path being followed to the red side of the field.
            // THE ORIGIN WILL REMAIN ON THE BLUE SIDE

            auto alliance = frc::DriverStation::GetAlliance();
            if (alliance) {
                return alliance.value() == frc::DriverStation::Alliance::kRed;
            }
            return false;
        },
        this // Reference to this subsystem to set requirements
    );
}



void CommandSwerveDrivetrain::AddClusterVisionMeasurments(){
    m_visionResults = m_visionCluster.GetVisionEstimates();
    if(m_visionResults.size() > 0){
        for (auto result : m_visionResults){
            AddVisionMeasurement(result.visionEstimate.estimatedPose.ToPose2d(), result.visionEstimate.timestamp, result.standardDeviations);
        }
    }
}

