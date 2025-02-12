// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/length.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>


#include "ctre/phoenix6/TalonFX.hpp"
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

    static constexpr int kCoralAngleMotor = 0; //not currently set
    static constexpr int kCoralIntakeMotor = 0; //not currently set 

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
        //    )
        //.WithFeedback(ctre::phoenix6::configs::FeedbackConfigs{}
        );

    static constexpr ctre::phoenix6::configs::TalonFXConfiguration kCoralIntakeConfigs = ctre::phoenix6::configs::TalonFXConfiguration{}
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

    static constexpr units::inch_t kLowerLimit = 0_tr;
    static constexpr units::inch_t kUpperLimit = 1000_tr;

}