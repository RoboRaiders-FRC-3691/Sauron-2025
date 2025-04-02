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

class ClimberSubsystem : public frc2::SubsystemBase {
    public:
        // ClimberSubsystem constructor
        ClimberSubsystem();

        // Periodic Method called periodically by the CommandScheduler
        void Periodic() override;

        // Sets climber angle
        frc2::CommandPtr SetAngle(units::angle::turn_t angle);

        // Checks if a given angle is within the limits of the climber
        // Returns true when valid and false when invalid
        bool ValidAngle(units::angle::turn_t angle);

        // Returns a refrence to the climber motor
        ctre::phoenix6::hardware::TalonFX& GetClimbMotor();

    private:
        // Declare the Climber motor
        ctre::phoenix6::hardware::TalonFX ClimbMotor;

        // Declare motion magic request
        ctre::phoenix6::controls::MotionMagicVoltage m_PoseRequest;

        // Declare Climber Cam
        cs::UsbCamera m_ClimberCam;
};
