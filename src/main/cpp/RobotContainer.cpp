// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/Commands.h>

RobotContainer::RobotContainer()
{
    ConfigureBindings();

    //Add Options to the sendable chooser
    //Default: No auto with value of int -1
    autoChooser.SetDefaultOption("No Auto", -1);
    
    //For loop to add an option for each value in PPautoVect.
    //The name is the auto command name and the value is i (the index of the auto)
    for(int i = 0; i < int(PPautoVect.size()); i++){
        autoChooser.AddOption(PPautoVect[i].GetName(), i);
    }

    frc::SmartDashboard::PutData("Auto Selector", &autoChooser);
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

    m_XboxController.POVLeft().WhileTrue(drivetrain.ApplyRequest([this]() -> auto&& { return brake; }));
    m_XboxController.POVRight().WhileTrue(drivetrain.ApplyRequest([this]() -> auto&& {
        return point.WithModuleDirection(frc::Rotation2d{-m_XboxController.GetLeftY(), -m_XboxController.GetLeftX()});
    }));

    // Run SysId routines when holding back/start and X/Y.
    // Note that each routine should be run exactly once in a single log.
    (m_XboxController.Back() && m_XboxController.Y()).WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kForward));
    (m_XboxController.Back() && m_XboxController.X()).WhileTrue(drivetrain.SysIdDynamic(frc2::sysid::Direction::kReverse));
    (m_XboxController.Start() && m_XboxController.Y()).WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kForward));
    (m_XboxController.Start() && m_XboxController.X()).WhileTrue(drivetrain.SysIdQuasistatic(frc2::sysid::Direction::kReverse));

    // reset the field-centric heading on left bumper press
    m_XboxController.LeftBumper().OnTrue(drivetrain.RunOnce([this] { drivetrain.SeedFieldCentric(); }));

    drivetrain.RegisterTelemetry([this](auto const &state) { logger.Telemeterize(state); });

    m_XboxController.A().WhileTrue(m_elevator.SetHeight(0_in));
    m_XboxController.B().WhileTrue(m_elevator.SetHeight(15_in));
    m_XboxController.X().WhileTrue(m_elevator.SetHeight(30_in));
    m_XboxController.Y().WhileTrue(m_elevator.SetHeight(48.875_in));

}

frc2::CommandPtr RobotContainer::GetAutonomousCommand(){
    //Grab the selected autoChooser option
    //If the value is -1 then do default(dont run an auto routine)
    //Otherwise the value of the autoChooser is the PPautoVect index for the auto selected  
    if(autoChooser.GetSelected() == -1){
        return frc2::cmd::Print("No Auto Selected");
    }
    else{
    return std::move(PPautoVect[autoChooser.GetSelected()]).ToPtr();
    }
}