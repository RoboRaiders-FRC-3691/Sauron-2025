// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <map>

#include <wpi/array.h>

#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/geometry/Rotation2d.h>

#include <units/length.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>
#include <units/time.h>

#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/TalonFXS.hpp"
#include "ctre/phoenix6/CANdi.hpp"
#include "ctre/phoenix6/CANcoder.hpp"

#include "ctre/phoenix6/configs/Configurator.hpp"
#include "ctre/phoenix6/configs/Configs.hpp"




/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace OperatorConstants {

    // Expected Xbox Controller port
    inline constexpr int kXboxControllerPort = 0;

    // Expected MacroPad port
    inline constexpr int kMacroPadPort = 1;

}  // namespace OperatorConstants

namespace VisionConstants {

    // Max pose ambiguity (for single tag)
    static constexpr double kMaxSingleTagAmbiguity = 0.2;
    static constexpr double kMaxMultiTagAmbiguity = 0.3;

    // Max distance (for single tag)
    static constexpr units::inch_t kMaxSingleTagDistance = 150_in;
    static constexpr units::inch_t kMaxMultiTagDistance = 200_in;
  
    // Default standard deviations 
    static constexpr wpi::array<double, 3U> kSingleTagStdDevs {3.75, 3.75, 7.5};
    static constexpr wpi::array<double, 3U> kMultiTagStdDevs {0.75, 0.75, 1.5};

    // Standard deviations scale factor limit (scaled as: distance^2 * kStdDevsScaleFactorLimit/(MaxTagDistance^2))
    static constexpr double kStdDevsScaleFactorLimit = 1.0 / 30.0;

}

namespace ElevatorConstants{

    // Variable to store the CAN bus used by the coral subsystem
    static constexpr std::string_view kElevatorCANLoop = "*"; // Note: for ctre star is "any CANivore seen by the program"

    // Elevator motor ports
    static constexpr int kElevatorMotorRightPort = 3; 
    static constexpr int kElevatorMotorLeftPort = 4;  

    // Elevator motor configs
    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kElevatorMotorConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.41)
            .WithKV(.12)
            .WithKA(.01)
            .WithKP(4.8)
            .WithKI(0)
            .WithKD(.1)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(150_tps)
            .WithMotionMagicAcceleration(250_tr_per_s_sq)
            .WithMotionMagicJerk(2500_tr_per_s_cu)
        );

    // Conversion between elevator heigh in inches and the number of elevator motor rotations
    static constexpr double kInPerRot = 0.4406;

    // Elevator height upper and lower limits
    static constexpr units::inch_t kLowerLimit = .75_in;
    static constexpr units::inch_t kUpperLimit = 48.875_in;

}

namespace CoralConstants{

    // Variable to store the CAN bus used by the coral subsystem
    static constexpr std::string_view kCoralCANLoop = ""; // Note: for ctre empty quotes is "RoboRIO"

    // Coral motor ports
    static constexpr int kCoralAngleMotorPort = 12; 
    static constexpr int kCoralIntakeMotorPort = 13;
    static constexpr int kCoralCANCoderPort = 26;

    // Coral CANdi port
    static constexpr int kCoralCANdiPort = 23;  

    // Coral angle motor configs
    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kCoralAngleConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.45)
            .WithKV(.17)
            .WithKA(.01)

            .WithKP(5)
            .WithKI(0)
            .WithKD(.12)

            .WithKG(0)
            .WithGravityType(ctre::phoenix6::signals::GravityTypeValue::Arm_Cosine)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(80_tps)
            .WithMotionMagicAcceleration(160_tr_per_s_sq)
            .WithMotionMagicJerk(1600_tr_per_s_cu)
        )
        .WithFeedback(ctre::phoenix6::configs::FeedbackConfigs{}
            .WithSensorToMechanismRatio(9) 
            .WithFeedbackRemoteSensorID(kCoralCANCoderPort)
            .WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RemoteCANcoder)
        );

    // Coral intake motor configs
    static constexpr ctre::phoenix6::configs::TalonFXSConfiguration kCoralIntakeConfigs = ctre::phoenix6::configs::TalonFXSConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.45)
            .WithKV(.08)
            .WithKA(.01)

            .WithKP(.25)
            .WithKI(0)
            .WithKD(.015)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(80_tps)
            .WithMotionMagicAcceleration(160_tr_per_s_sq)
            .WithMotionMagicJerk(1600_tr_per_s_cu)
        )
        .WithCommutation(ctre::phoenix6::configs::CommutationConfigs{}
            .WithMotorArrangement(ctre::phoenix6::signals::MotorArrangementValue::Minion_JST)
        )
        .WithMotorOutput(ctre::phoenix6::configs::MotorOutputConfigs{}
            .WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive)
        )
        .WithExternalFeedback(ctre::phoenix6::configs::ExternalFeedbackConfigs{}
            .WithSensorToMechanismRatio(1)  
        );

    // Coral CANCoder config
    static constexpr ctre::phoenix6::configs::CANcoderConfiguration kCoralCANCoderConfigs = ctre::phoenix6::configs::CANcoderConfiguration{}
        .WithMagnetSensor(ctre::phoenix6::configs::MagnetSensorConfigs{}
            .WithMagnetOffset(-.114502_tr)
        );

    // Coral angle upper and lower limits
    // Currently defined as 0 and 1000 as coral limits are not yet defined
    static constexpr units::turn_t kLowerLimit = -.3_tr; 
    static constexpr units::turn_t kUpperLimit = .3_tr;

    // Coral CANdi configs
    static constexpr ctre::phoenix6::configs::CANdiConfiguration kCoralCANdiConfig = ctre::phoenix6::configs::CANdiConfiguration{}
        .WithDigitalInputs(ctre::phoenix6::configs::DigitalInputsConfigs{}
            .WithS1FloatState(ctre::phoenix6::signals::S1FloatStateValue::PullHigh)
            .WithS1CloseState(ctre::phoenix6::signals::S1CloseStateValue::CloseWhenLow)
        );
    
    // Arrays for the coral placement heights, and the coral placement angles. Index = Level - 1. (e.g. L1 = [0])
    static constexpr wpi::array<units::length::inch_t, 4U> kCoralPlacementHeights = {2.5_in, 17_in, 28_in, 48.875_in};
    static constexpr wpi::array<units::angle::turn_t, 4U> kCoralPlacementCoralAngles = {.01_tr, .04_tr, .07_tr, .10_tr};//{0.06_tr, 0.09_tr, .12_tr, .15_tr};
    static constexpr wpi::array<units::angle::turn_t, 4U> kCoralPlacementAlgaeAngles = {.04_tr, .04_tr, .04_tr, .04_tr};
    
    static constexpr units::angle::turn_t kCoralIntakeAngle = .25_tr;
    static constexpr units::angular_velocity::revolutions_per_minute_t kCoralIntakeVelocity = 3000_rpm;
    static constexpr units::time::second_t kCoralPlacementTime = 3_s;
}

namespace AlgaeConstants{

    // Variable to store the CAN bus used by the coral subsystem
    static constexpr std::string_view kAlgaeCANLoop = ""; // Note: for ctre empty quotes is "RoboRIO"

    // Algae motor ports
    static constexpr int kAlgaeAngleMotorPort = 11; 
    static constexpr int kAlgaeIntakeMotorPort = 7;
    static constexpr int kAlgaeCANCoderPort = 27;

    // Algae angle motor configs
    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kAlgaeAngleConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.25)
            .WithKV(.20)
            .WithKA(.015)
            
            .WithKP(8.5)
            .WithKI(0)
            .WithKD(.25)

            .WithKG(.3)
            .WithGravityType(ctre::phoenix6::signals::GravityTypeValue::Arm_Cosine)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(80_tps)
            .WithMotionMagicAcceleration(70_tr_per_s_sq)
            .WithMotionMagicJerk(1000_tr_per_s_cu)
        )
        .WithFeedback(ctre::phoenix6::configs::FeedbackConfigs{}
            .WithSensorToMechanismRatio(36)
            .WithFeedbackRemoteSensorID(kAlgaeCANCoderPort)
            .WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RemoteCANcoder)
        );

    // Algae intake motor configs
    static constexpr ctre::phoenix6::configs::TalonFXSConfiguration kAlgaeIntakeConfigs = ctre::phoenix6::configs::TalonFXSConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.45)
            .WithKV(.08)
            .WithKA(.01)

            .WithKP(.25)
            .WithKI(0)
            .WithKD(.015)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(80_tps)
            .WithMotionMagicAcceleration(160_tr_per_s_sq)
            .WithMotionMagicJerk(1600_tr_per_s_cu)
        )
        .WithCommutation(ctre::phoenix6::configs::CommutationConfigs{}
            .WithMotorArrangement(ctre::phoenix6::signals::MotorArrangementValue::Minion_JST)
        )
        .WithExternalFeedback(ctre::phoenix6::configs::ExternalFeedbackConfigs{}
            .WithSensorToMechanismRatio(16)  
        );

    // Algae CANCoder config
    static constexpr ctre::phoenix6::configs::CANcoderConfiguration kAlgaeCANCoderConfigs = ctre::phoenix6::configs::CANcoderConfiguration{}
        .WithMagnetSensor(ctre::phoenix6::configs::MagnetSensorConfigs{}
            .WithMagnetOffset(.380699_tr)
            .WithSensorDirection(ctre::phoenix6::signals::InvertedValue::Clockwise_Positive)
        );

    // Algae angle upper and lower limits
    // Currently defined as -1000 and 1000 as algae limits are not yet defined
    static constexpr units::turn_t kLowerLimit = -.3_tr;
    static constexpr units::turn_t kUpperLimit = .3_tr;
    
    
    //Arrays for the algae removal heights, and the algae removal angles. Index = Level - 2. (e.g. L2 = [0]). Note: Algae is only removed from L2 and L3.
    static constexpr wpi::array<units::length::inch_t, 2U> kAlgaeRemovalHeights = {22_in, 38_in};
    static constexpr wpi::array<units::angle::turn_t, 2U> kAlgaeRemovalCoralAngles = {.32_tr, .32_tr};
    static constexpr wpi::array<units::angle::turn_t, 2U> kAlgaeRemovalAlgaeAngles = {-0.1_tr, -0.1_tr};

    // Predifined removal velocity and time
    // Currently not used
    static constexpr units::angular_velocity::revolutions_per_minute_t kAlgaeIntakeVelocity = 3000_rpm;
    static constexpr units::time::second_t kAlgaeRemovalTime = 3_s;

}


namespace ClimberConstants{

    // Variable to store the CAN bus used by the climber subsystem
    static constexpr std::string_view kClimberCANLoop = "*"; // Note: for ctre star is "any CANivore seen by the program"

    // Climber motor port
    static constexpr int kClimberMotorPort = 10; 

    // Climber motor configs (sensor to mechanism ratio currently wrong at 1:1)
    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kClimberMotorConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.41)
            .WithKV(.15)
            .WithKA(.1)

            .WithKP(9)
            .WithKI(0)
            .WithKD(.7)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(120_tps)
            .WithMotionMagicAcceleration(360_tr_per_s_sq)
            .WithMotionMagicJerk(2000_tr_per_s_cu)
        )
        .WithFeedback(ctre::phoenix6::configs::FeedbackConfigs{}
            .WithSensorToMechanismRatio(125)
        );


    static constexpr units::angle::turn_t kClimberDown = -2_tr;
    static constexpr units::angle::turn_t kClimberUp = 1.5_tr;
    


    // Climber angle upper and lower limits
    // Currently limits are conservative
    static constexpr units::angle::turn_t kLowerLimit = -15_tr;
    static constexpr units::angle::turn_t kUpperLimit = 15_tr;

}

namespace AutoConstants{
    static const std::map<char, frc::Pose2d> kReefPositions{
    {'A', frc::Pose2d(frc::Translation2d(110_in, 70_in), frc::Rotation2d(0_deg))},
    {'B', frc::Pose2d(frc::Translation2d(212_in, 202_in), frc::Rotation2d(-120_deg))},
    {'C', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'D', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'E', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'F', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'G', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'H', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'I', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'J', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'K', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))},
    {'L', frc::Pose2d(frc::Translation2d(0_in, 0_in), frc::Rotation2d(0_deg))}
};
}