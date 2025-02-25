// No Copyright (c) 

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "units/length.h"
#include "units/angle.h"

#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/configs/Configs.hpp"
#include "ctre/phoenix6/configs/Configurator.hpp"

#include "Constants.h"

class ElevatorSubsystem : public frc2::SubsystemBase {
    public:
        //ElevatorSubsystem constructor
        ElevatorSubsystem();

        void Periodic();

        //Converts a number of rotations into a height for the elevator
        units::inch_t RotationsToHeight(units::turn_t turns);

        //Converts a height into a number of rotations for the elevator motor
        units::turn_t HeightToRotations(units::inch_t height);

        //Sets elevator height
        frc2::CommandPtr SetHeight(units::inch_t height);

        //Gets elevator height
        units::inch_t GetHeight();

        //Checks if a given height is within the limits of the elevator
        bool ValidHeight(units::inch_t height);

    private:
        //Declare the elevator motors
        ctre::phoenix6::hardware::TalonFX RightMotor;
        ctre::phoenix6::hardware::TalonFX LeftMotor;
        ctre::phoenix6::controls::MotionMagicVoltage m_PoseRequest;

};
