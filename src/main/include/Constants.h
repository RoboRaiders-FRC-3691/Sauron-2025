// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <wpi/array.h>

#include <units/length.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>
#include <units/time.h>

#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/TalonFXS.hpp"
#include "ctre/phoenix6/CANdi.hpp"

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

    inline constexpr int kXboxControllerPort = 0;
    inline constexpr int kMacroPadPort = 1;

}  // namespace OperatorConstants

namespace VisionConstants {

    //Max pose ambiguity (for single tag)
    static constexpr double kMaxSingleTagAmbiguity = 0.2;
    static constexpr double kMaxMultiTagAmbiguity = 0.3;

    //Max distance (for single tag)
    static constexpr units::inch_t kMaxSingleTagDistance = 150_in;
    static constexpr units::inch_t kMaxMultiTagDistance = 200_in;
  
    //Default standard deviations 
    static constexpr wpi::array<double, 3U> kSingleTagStdDevs {3.75, 3.75, 7.5};
    static constexpr wpi::array<double, 3U> kMultiTagStdDevs {0.75, 0.75, 1.5};

    //Standard deviations scale factor limit (scaled as: distance^2 * kStdDevsScaleFactorLimit/(MaxTagDistance^2))
    static constexpr double kStdDevsScaleFactorLimit = 1.0 / 30.0;

    
}

namespace ElevatorConstants{

    //Variable to store the CAN bus used by the coral subsystem these star for "any CANivore seen by the program"
    static constexpr std::string_view kElevatorCANLoop = "*"; 

    static constexpr int kElevatorMotorRightPort = 3; 
    static constexpr int kElevatorMotorLeftPort = 4;  

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

    static constexpr double kInPerRot = 0.4406;

    static constexpr units::inch_t kLowerLimit = .75_in;
    static constexpr units::inch_t kUpperLimit = 48.875_in;

}

namespace CoralConstants{

    //Variable to store the CAN bus used by the coral subsystem these star for "any CANivore seen by the program"
    static constexpr std::string_view kCoralCANLoop = ""; 

    static constexpr int kCoralAngleMotorPort = 12; 
    static constexpr int kCoralIntakeMotorPort = 13;  

    static constexpr int kCoralCANdiPort = 23;  

    //Config constants and limits are preliminary and need to be fine tuned.
    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kCoralAngleConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.45)
            .WithKV(.17)
            .WithKA(.01)
            .WithKP(5)
            .WithKI(0)
            .WithKD(.12)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(80_tps)
            .WithMotionMagicAcceleration(160_tr_per_s_sq)
            .WithMotionMagicJerk(1600_tr_per_s_cu)
        )
        .WithFeedback(ctre::phoenix6::configs::FeedbackConfigs{}
            .WithSensorToMechanismRatio(9) 
        );

     
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

    static constexpr units::turn_t kLowerLimit = 0_tr;
    static constexpr units::turn_t kUpperLimit = 1000_tr;


    static constexpr ctre::phoenix6::configs::CANdiConfiguration kCoralCANdiConfig = ctre::phoenix6::configs::CANdiConfiguration{}
        .WithDigitalInputs(ctre::phoenix6::configs::DigitalInputsConfigs{}
            .WithS1FloatState(ctre::phoenix6::signals::S1FloatStateValue::PullHigh)
            .WithS1CloseState(ctre::phoenix6::signals::S1CloseStateValue::CloseWhenLow)
        );
    
    //Arrays for the coral placement heights, and the coral placement angles. Index = Level - 1. (e.g. L1 = [0])
    static constexpr wpi::array<units::length::inch_t, 4U> kCoralPlacementHeights = {0.75_in, 11_in, 25_in, 48.875_in}; //{2.5_in, 17_in, 28_in, 48.875_in}
    static constexpr wpi::array<units::angle::turn_t, 4U> kCoralPlacementCoralAngles = {0.01_tr, 0.054_tr, .084_tr, .10_tr};//{0.06_tr, 0.09_tr, .12_tr, .15_tr}; //{0.01_tr, 0.04_tr, .07_tr, .10_tr}
    static constexpr wpi::array<units::angle::turn_t, 4U> kCoralPlacementAlgaeAngles = {0_tr, 0_tr, 0_tr, 0_tr}; //0.4 before 3/8/2025
    
    static constexpr units::angular_velocity::revolutions_per_minute_t kCoralPlacementVelocity = -750_rpm;
    static constexpr units::time::second_t kCoralPlacementTime = 3_s;
}

namespace AlgaeConstants{

    //Variable to store the CAN bus used by the coral subsystem these star for "any CANivore seen by the program"
    static constexpr std::string_view kAlgaeCANLoop = ""; 

    static constexpr int kAlgaeAngleMotorPort = 11; 
    static constexpr int kAlgaeIntakeMotorPort = 7;  

    //Config constants and limits are preliminary and need to be fine tuned.
    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kAlgaeAngleConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.25)
            .WithKV(.20)
            .WithKA(.015)
            .WithKG(.3)
            
            .WithKP(8.5)
            .WithKI(0)
            .WithKD(.25)
            .WithGravityType(ctre::phoenix6::signals::GravityTypeValue::Arm_Cosine)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(80_tps)
            .WithMotionMagicAcceleration(70_tr_per_s_sq)
            .WithMotionMagicJerk(1000_tr_per_s_cu)
        )
        .WithFeedback(ctre::phoenix6::configs::FeedbackConfigs{}
            .WithSensorToMechanismRatio(36)
        );

     
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

    static constexpr units::turn_t kLowerLimit = -1000_tr;
    static constexpr units::turn_t kUpperLimit = 1000_tr;
    
    
    //Arrays for the algae removal heights, and the algae removal angles. Index = Level - 2. (e.g. L2 = [0]). Note: Algae is only removed from L2 and L3.
    static constexpr wpi::array<units::length::inch_t, 2U> kAlgaeRemovalHeights = {22_in, 38_in};
    static constexpr wpi::array<units::angle::turn_t, 2U> kAlgaeRemovalCoralAngles = {.32_tr, .32_tr};
    static constexpr wpi::array<units::angle::turn_t, 2U> kAlgaeRemovalAlgaeAngles = {-0.1_tr, -0.1_tr};

    static constexpr units::angular_velocity::revolutions_per_minute_t kAlgaeRemovalVelocity = 1000_rpm;
    static constexpr units::time::second_t kAlgaeRemovalTime = 3_s;

}


namespace ClimberConstants{

    //Variable to store the CAN bus used by the coral subsystem these star for "any CANivore seen by the program"
    static constexpr std::string_view kClimberCANLoop = "*"; 

    static constexpr int kClimberMotorPort = 10; 

    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kClimberMotorConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.41)
            .WithKV(.12)
            .WithKA(.01)
            .WithKP(4.8)
            .WithKI(0)
            .WithKD(.1)
        )
        .WithMotionMagic(ctre::phoenix6::configs::MotionMagicConfigs{}
            .WithMotionMagicCruiseVelocity(80_tps)
            .WithMotionMagicAcceleration(160_tr_per_s_sq)
            .WithMotionMagicJerk(1600_tr_per_s_cu)
        );

    static constexpr units::angle::turn_t kLowerLimit = -700_tr;
    static constexpr units::angle::turn_t kUpperLimit = 0_tr;

}
