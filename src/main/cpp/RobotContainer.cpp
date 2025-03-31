// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() : m_DashOrchestra(frc::filesystem::GetDeployDirectory().append("/Music/"))
{

    PathPlannerSetUp();

    OrchestraSetUp();
    
    ConfigureBindings();
}

void RobotContainer::ConfigureBindings()
{
    // Note that X is defined as forward according to WPILib convention,
    // and Y is defined as to the left according to WPILib convention.
    drivetrain.SetDefaultCommand(
        // Drivetrain will execute this command periodically
        drivetrain.ApplyRequest([this]() -> auto&& {
            return drive.WithVelocityX(-m_XboxController.GetLeftY() * MaxSpeed) // Drive forward with negative Y (forward)
                .WithVelocityY(-m_XboxController.GetLeftX() * MaxSpeed) // Drive left with negative X (left)
                .WithRotationalRate(-m_XboxController.GetRightX() * MaxAngularRate); // Drive counterclockwise with negative X (left)
        })
    );


    // m_XboxController.POVLeft().WhileTrue(drivetrain.ApplyRequest([this]() -> auto&& { return brake; }));
    // m_XboxController.POVRight().WhileTrue(drivetrain.ApplyRequest([this]() -> auto&& {
    //     return point.WithModuleDirection(frc::Rotation2d{-m_XboxController.GetLeftY(), -m_XboxController.GetLeftX()});
    // })); // Commented out for debugging

    // Run SysId routines when holding back/start and X/Y.
    // Note that each routine should be run exactly once in a single log.
    (m_XboxController.Back() && m_XboxController.Y()).WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kForward));
    (m_XboxController.Back() && m_XboxController.X()).WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kReverse));
    (m_XboxController.Start() && m_XboxController.Y()).WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kForward));
    (m_XboxController.Start() && m_XboxController.X()).WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kReverse));

    // reset the field-centric heading on Y button press (causes diver disorientation if used fequntly)
    //m_XboxController.Y().OnTrue(drivetrain.RunOnce([this] { drivetrain.SeedFieldCentric(); }));

    drivetrain.RegisterTelemetry([this](auto const &state) { logger.Telemeterize(state); });
    
    // Coral controls
    m_XboxController.RightBumper().WhileTrue(m_Coral.RunIntake(-1 * CoralConstants::kCoralIntakeVelocity));
    m_XboxController.LeftBumper().WhileTrue(m_Coral.RunIntake(CoralConstants::kCoralIntakeVelocity));
    
    // Coral Intake Angle
    m_XboxController.X().OnTrue(m_Coral.SetAngle(CoralConstants::kCoralIntakeAngle));

    // Algae controls
    m_XboxController.RightTrigger().WhileTrue(m_Algae.RunIntake(AlgaeConstants::kAlgaeIntakeVelocity));
    m_XboxController.LeftTrigger().WhileTrue(m_Algae.RunIntake(-1 * AlgaeConstants::kAlgaeIntakeVelocity));

    // Algae Intake Angle
    m_XboxController.B().OnTrue(m_Algae.SetAngle(AlgaeConstants::kAlgaeFloorIntakeAlgaeAngle));


    // Reef Positions Coral and Algae
    m_MacroPad.GetKey(4,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 0));
    m_MacroPad.GetKey(3,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 1));
    m_MacroPad.GetKey(2,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 2));
    m_MacroPad.GetKey(1,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 3));

    m_MacroPad.GetKey(1,2).OnTrue(ReefCommands::RemoveAlgaeAtLevel(m_Coral, m_Algae, m_elevator, 1));
    m_MacroPad.GetKey(2,2).OnTrue(ReefCommands::RemoveAlgaeAtLevel(m_Coral, m_Algae, m_elevator, 0));
    m_MacroPad.GetKey(3,2).OnTrue(ReefCommands::AlgaeProcessor(m_Coral, m_Algae, m_elevator));



    // Climber controls
    m_MacroPad.GetKey(1, 1).OnTrue(m_Climber.SetAngle(ClimberConstants::kClimberUp));
    m_MacroPad.GetKey(2, 1).OnTrue(m_Climber.SetAngle(ClimberConstants::kClimberDown));


    // Debug/Testing controls (likely remove before Minneapolis)
    m_XboxController.A().WhileTrue(m_elevator.SetHeight(5_in));

    // Testing pathfind to position
    (m_XboxController.Back() && m_XboxController.POVRight()).OnTrue(drivetrain.ReefLineUp('A'));
}

void RobotContainer::OrchestraSetUp(){
    // Add all the swerve modules to the orchestra
    for (auto& module : drivetrain.GetModules()){
        m_DashOrchestra.AddInstrument(module->GetDriveMotor());
        m_DashOrchestra.AddInstrument(module->GetSteerMotor());
    }

    // Add the left and right elevator motors to the orchestra
    m_DashOrchestra.AddInstrument(m_elevator.GetRightMotor());
    m_DashOrchestra.AddInstrument(m_elevator.GetLeftMotor());

    // Add the Coral and Algae Talon FX (Angle Motors) to the orchestra
    m_DashOrchestra.AddInstrument(m_Coral.GetAngleMotor());
    m_DashOrchestra.AddInstrument(m_Algae.GetAngleMotor());

    // Add the Climber motor to the orchestra
    m_DashOrchestra.AddInstrument(m_Climber.GetClimbMotor());

    // Start the orchestra dashboard interface
    m_DashOrchestra.InitDashboardInterface();
}

void RobotContainer::PathPlannerSetUp(){
    
    drivetrain.ConfigurePathPlanner();

    // Some preliminary Named Command Implementations
    pathplanner::NamedCommands::registerCommand("Align Coral L1", ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 0));
    pathplanner::NamedCommands::registerCommand("Align Coral L2", ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 1));
    pathplanner::NamedCommands::registerCommand("Align Coral L3", ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 2));
    pathplanner::NamedCommands::registerCommand("Align Coral L4", ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 3));

    pathplanner::NamedCommands::registerCommand("Coral Intake", m_Coral.RunIntakeFor((-1 * CoralConstants::kCoralIntakeVelocity), CoralConstants::kCoralPlacementTime)); // Could be labled backwards (Intake <-> Dispense)
    pathplanner::NamedCommands::registerCommand("Coral Dispense", m_Coral.RunIntakeFor(CoralConstants::kCoralIntakeVelocity, CoralConstants::kCoralPlacementTime));

    pathplanner::NamedCommands::registerCommand("Algae Intake", m_Algae.RunIntakeFor(AlgaeConstants::kAlgaeIntakeVelocity, AlgaeConstants::kAlgaeRemovalTime)); // Could be labled backwards (Intake <-> Dispense)
    pathplanner::NamedCommands::registerCommand("Algae Dispense", m_Algae.RunIntakeFor((-1 * AlgaeConstants::kAlgaeIntakeVelocity), AlgaeConstants::kAlgaeRemovalTime));

    // Add Options to the sendable chooser
    autoChooser = pathplanner::AutoBuilder::buildAutoChooser();

    frc::SmartDashboard::PutData("Auto Selector", &autoChooser);
}


frc2::Command* RobotContainer::GetAutonomousCommand(){
    // Grab the selected autoChooser option
    return autoChooser.GetSelected();
}
