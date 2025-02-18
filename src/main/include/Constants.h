// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/length.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>

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

    inline constexpr int kDriverControllerPort = 0;

}  // namespace OperatorConstants

namespace ElevatorConstants{

    //Variable to store the CAN bus used by the coral subsystem these star for "any CANivore seen by the program"
    static constexpr std::string_view kElevatorCANLoop = "*"; 

    static constexpr int kElevatorMotorRightPort = 12; //not currently set
    static constexpr int kElevatorMotorLeftPort = 15; //not currently set 

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

    static constexpr units::inch_t kLowerLimit = 0_in;
    static constexpr units::inch_t kUpperLimit = 48.875_in;

}

namespace CoralConstants{

    //Variable to store the CAN bus used by the coral subsystem these star for "any CANivore seen by the program"
    static constexpr std::string_view kCoralCANLoop = "*"; 

    static constexpr int kCoralAngleMotorPort = 0; //not currently set
    static constexpr int kCoralIntakeMotorPort = 0; //not currently set 

    static constexpr int kCoralCANdiPort = 0; //not currently set 

    //Config constants and limits are preliminary and need to be fine tuned.
    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kCoralAngleConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.25)
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
        )
        .WithFeedback(ctre::phoenix6::configs::FeedbackConfigs{}
            .WithSensorToMechanismRatio(9)  
        );

     
    static constexpr ctre::phoenix6::configs::TalonFXSConfiguration kCoralIntakeConfigs = ctre::phoenix6::configs::TalonFXSConfiguration{}
        .WithSlot0(ctre::phoenix6::configs::Slot0Configs{}
            .WithKS(.25)
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

    static constexpr units::turn_t kLowerLimit = 0_tr;
    static constexpr units::turn_t kUpperLimit = 1000_tr;


    static constexpr ctre::phoenix6::configs::CANdiConfiguration kCoralCANdiConfig = ctre::phoenix6::configs::CANdiConfiguration{}
        .WithDigitalInputs(ctre::phoenix6::configs::DigitalInputsConfigs{}
            .WithS1FloatState(ctre::phoenix6::signals::S1FloatStateValue::PullHigh)
            .WithS1CloseState(ctre::phoenix6::signals::S1CloseStateValue::CloseWhenLow)
        );
    

}

namespace VisionConstants {

    //Max pose ambiguity (for single tag)
    constexpr double kMaxSingleTagAmbiguity = 0.2;
    constexpr double kMaxMultiTagAmbiguity = 0.3;

    //Max distance (for single tag)
    constexpr units::inch_t kMaxSingleTagDistance = 150_in;
    constexpr units::inch_t kMaxMultiTagDistance = 200_in;
  
    //Default standard deviations 
    constexpr wpi::array<double, 3U> kSingleTagStdDevs {3.75, 3.75, 7.5};
    constexpr wpi::array<double, 3U> kMultiTagStdDevs {0.75, 0.75, 1.5};

    //Standard deviations scale factor limit (scaled as: distance^2 * kStdDevsScaleFactorLimit/(MaxTagDistance^2))
    constexpr double kStdDevsScaleFactorLimit = 1.0 / 30.0;

    
}