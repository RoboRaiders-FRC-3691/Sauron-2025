// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() : m_DashOrchestra(frc::filesystem::GetDeployDirectory().append("/Music/"))
{
    ConfigureBindings();

    OrchestraSetUp();

    PathPlannerSetUp();
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

    // reset the field-centric heading on Y button press (causes diver disorientation if used fequrnly)
    //m_XboxController.Y().OnTrue(drivetrain.RunOnce([this] { drivetrain.SeedFieldCentric(); }));

    drivetrain.RegisterTelemetry([this](auto const &state) { logger.Telemeterize(state); });


    m_XboxController.RightTrigger().WhileTrue(m_Algae.RunIntake(3000_rpm));
    m_XboxController.LeftTrigger().WhileTrue(m_Algae.RunIntake(-3000_rpm));


    m_MacroPad.GetKey(4,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 0));
    m_MacroPad.GetKey(3,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 1));
    m_MacroPad.GetKey(2,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 2));
    m_MacroPad.GetKey(1,3).OnTrue(ReefCommands::PlaceCoralAtLevel(m_Coral, m_Algae, m_elevator, 3));

    m_MacroPad.GetKey(1,2).OnTrue(ReefCommands::RemoveAlgaeAtLevel(m_Coral, m_Algae, m_elevator, 1));
    m_MacroPad.GetKey(2,2).OnTrue(ReefCommands::RemoveAlgaeAtLevel(m_Coral, m_Algae, m_elevator, 0));

    //Coral controls
    m_XboxController.RightBumper().WhileTrue(m_Coral.RunIntake(-3000_rpm));
    m_XboxController.LeftBumper().WhileTrue(m_Coral.RunIntake(3000_rpm));

    m_XboxController.B().OnTrue(m_Coral.SetAngle(.27_tr));
    m_XboxController.A().WhileTrue(m_elevator.SetHeight(5_in));

    //Temp Test Coral Intake Angle
    m_XboxController.X().OnTrue(m_Coral.SetAngle(.25_tr));

    //Climber controls
    m_MacroPad.GetKey(1, 1).OnTrue(m_Climber.SetAngle(-700_tr));
    m_MacroPad.GetKey(2, 1).OnTrue(m_Climber.SetAngle(-340_tr));
    m_MacroPad.GetKey(3, 1).OnTrue(m_Climber.SetAngle(-10_tr));
}

void RobotContainer::OrchestraSetUp(){
    //Add all the swerve modules to the orchestra
    for (auto& module : drivetrain.GetModules()){
        m_DashOrchestra.AddInstrument(module->GetDriveMotor());
        m_DashOrchestra.AddInstrument(module->GetSteerMotor());
    }

    //Add the left and right elevator motors to the orchestra
    m_DashOrchestra.AddInstrument(m_elevator.GetRightMotor());
    m_DashOrchestra.AddInstrument(m_elevator.GetLeftMotor());

    //Add the Coral and Algae Talon FX (Angle Motors) to the orchestra
    m_DashOrchestra.AddInstrument(m_Coral.GetAngleMotor());
    m_DashOrchestra.AddInstrument(m_Algae.GetAngleMotor());

    //Add the Climber motor to the orchestra
    m_DashOrchestra.AddInstrument(m_Climber.GetClimbMotor());

    //Start the orchestra dashboard interface
    m_DashOrchestra.InitDashboardInterface();
}

void RobotContainer::PathPlannerSetUp(){
    
    drivetrain.ConfigurePathPlanner();

    //Add Options to the sendable chooser
    //Default: No auto with value of int -1
    autoChooser = pathplanner::AutoBuilder::buildAutoChooser();

    frc::SmartDashboard::PutData("Auto Selector", &autoChooser);
}


frc2::Command* RobotContainer::GetAutonomousCommand(){
    //Grab the selected autoChooser option
    return autoChooser.GetSelected();
}
