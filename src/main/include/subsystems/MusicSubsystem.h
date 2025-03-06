#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "ctre/phoenix6/Orchestra.hpp"
#include "ctre/phoenix6/TalonFX.hpp"

class MusicSubsystem : public frc2::SubsystemBase {
    public:
        //MusicSubsystem Constructor
        MusicSubsystem();

        //Function called periodically whenever the CommandScheduler runs.
        void Periodic() override;

    private:
        ctre::phoenix6::Orchestra m_Orchestra;
        
};