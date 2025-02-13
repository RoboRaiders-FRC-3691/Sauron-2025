// No Copyright (c) 

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "units/angular_velocity.h"
#include "units/angle.h"

#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/TalonFXS.hpp"
#include "ctre/phoenix6/CANdi.hpp"

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

        frc2::CommandPtr SetIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity);

        frc2::CommandPtr RunIntakeFor(units::angular_velocity::revolutions_per_minute_t intakeVelocity, units::time::second_t timeout);

        //frc2::CommandPtr IntakeWithSensor(units::angular_velocity::revolutions_per_minute_t intakeVelocity); WIP see .cpp

        //Gets coral mechanism angle
        units::turn_t GetAngle();

        //Checks if a given angle is inside of the coral mechanism angle limits
        bool ValidAngle(units::degree_t angle);

    private:
        //Declare the coral motors
        ctre::phoenix6::hardware::TalonFX AngleMotor;
        ctre::phoenix6::hardware::TalonFXS IntakeMotor;

        //Declare coral CANdi
        ctre::phoenix6::hardware::CANdi IntakeSwitch;

        ctre::phoenix6::controls::MotionMagicTorqueCurrentFOC m_PoseRequest;
        ctre::phoenix6::controls::MotionMagicVelocityTorqueCurrentFOC m_VelRequest;

};
