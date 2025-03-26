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

class AlgaeSubsystem : public frc2::SubsystemBase {
    public:
        // AlgaeSubsystem constructor
        AlgaeSubsystem();

        // Periodic Method called periodically by the CommandScheduler
        void Periodic() override;

        // Returns a command that sets the algae mechanism angle
        frc2::CommandPtr SetAngle(units::angle::turn_t angle);

        // Returns a command that sets the intake velocity to a given value
        frc2::CommandPtr SetIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity);

        // Returns a command that runs the intake at intakeVelocity until interupted
        frc2::CommandPtr RunIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity);

        // Returns a command that runs the intake at intakeVelocity for "timeout" seconds when called
        frc2::CommandPtr RunIntakeFor(units::angular_velocity::revolutions_per_minute_t intakeVelocity, units::time::second_t timeout);

        // Returns the current algae mechanism angle
        units::turn_t GetAngle();

        // Checks if a given angle is inside of the algae mechanism angle limits
        // Returns true when valid and false when invalid
        bool ValidAngle(units::degree_t angle);

        // Returns a refrence to the coral angle motor
        ctre::phoenix6::hardware::TalonFX& GetAngleMotor();

        // Returns a refrence to the coral intake motor
        ctre::phoenix6::hardware::TalonFXS& GetIntakeMotor();

    private:
        // Declare the algae motors
        ctre::phoenix6::hardware::TalonFX AngleMotor;
        ctre::phoenix6::hardware::TalonFXS IntakeMotor;

        ctre::phoenix6::hardware::CANcoder CANCoder;

        // Declare motion magic requests
        ctre::phoenix6::controls::MotionMagicVoltage m_PoseRequest;
        ctre::phoenix6::controls::MotionMagicVelocityVoltage m_VelRequest;

};
