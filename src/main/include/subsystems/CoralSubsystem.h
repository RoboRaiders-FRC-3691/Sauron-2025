// No Copyright (c) 

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "units/angle.h"

#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/TalonFXS.hpp"
#include "ctre/phoenix6/configs/Configs.hpp"
#include "ctre/phoenix6/configs/Configurator.hpp"

#include "Constants.h"

class CoralSubsystem : public frc2::SubsystemBase {
    public:
        //CoralSubsystem constructor
        CoralSubsystem();

        void Periodic();

        //Sets the coral mechanism Angle
        frc2::CommandPtr SetAngle(units::degree_t angle);

        //Gets elevator height
        units::turn_t GetAngle();

        //Checks if a given angle is inside of the coral mechanism angle limits
        bool ValidAngle(units::degree_t angle);

    private:
        //Declare the elevator motors
        ctre::phoenix6::hardware::TalonFX AngleMotor;
        ctre::phoenix6::hardware::TalonFX IntakeMotor;
        ctre::phoenix6::controls::MotionMagicVoltage m_Request;

};
