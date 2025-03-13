// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <filesystem>
#include <frc/Filesystem.h>

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include "Utils/MacroPad/CommandAdafruitMacroPad.h"
#include "subsystems/CommandSwerveDrivetrain.h"
#include "Utils/Widgets/SwerveWidget.h"
#include "Utils/Widgets/DashboardOrchestra.h"
#include "Utils/AddressableRGB/DynamicLighting.h"

#include <frc/smartdashboard/SendableChooser.h>

#include <pathplanner/lib/commands/PathPlannerAuto.h>

#include "generated/TunerConstants.h"
#include "Telemetry.h"
#include "Constants.h"
#include "subsystems/ElevatorSubsystem.h"
#include "subsystems/CoralSubsystem.h"
#include "subsystems/ClimberSubsystem.h"

#include "CommandGroups/ReefCommands.h"

class RobotContainer {
private:
    units::meters_per_second_t MaxSpeed = TunerConstants::kSpeedAt12Volts; // kSpeedAt12Volts desired top speed
    units::radians_per_second_t MaxAngularRate = 0.75_tps; // 3/4 of a rotation per second max angular velocity

    /* Setting up bindings for necessary control of the swerve drive platform */
    swerve::requests::FieldCentric drive = swerve::requests::FieldCentric{}
        .WithDeadband(MaxSpeed * 0.1).WithRotationalDeadband(MaxAngularRate * 0.1) // Add a 10% deadband
        .WithDriveRequestType(swerve::DriveRequestType::OpenLoopVoltage); // Use open-loop control for drive motors
    swerve::requests::SwerveDriveBrake brake{};
    swerve::requests::PointWheelsAt point{};

    /* Note: This must be constructed before the drivetrain, otherwise we need to
     *       define a destructor to un-register the telemetry from the drivetrain */
    Telemetry logger{MaxSpeed};

    frc2::CommandXboxController m_XboxController{OperatorConstants::kXboxControllerPort};
    CommandAdafruitMacroPad m_MacroPad{OperatorConstants::kMacroPadPort};

public:
    subsystems::CommandSwerveDrivetrain drivetrain{TunerConstants::CreateDrivetrain()};

    RobotContainer();

    frc2::Command* GetAutonomousCommand();

private:
    void ConfigureBindings();

    ElevatorSubsystem m_elevator;
    CoralSubsystem m_Coral;
    AlgaeSubsystem m_Algae;
    ClimberSubsystem m_Climber;
    
    void OrchestraSetUp();

    Widgets::DashboardOrchestra m_DashOrchestra;

    void PathPlannerSetUp();
    
    frc::SendableChooser<frc2::Command*> autoChooser;

    // RGB testing
    void TestingLights();

    AddressableRGB::DynamicLighting m_lightTesting;
};
