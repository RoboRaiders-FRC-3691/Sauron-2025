#pragma once

#include <memory>

#include <filesystem>
#include <frc/Filesystem.h>

#include <frc2/command/Commands.h>
#include <frc2/command/button/NetworkButton.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/Trigger.h>

#include "ctre/phoenix6/Orchestra.hpp"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "Utils/Widgets/CommandDashboardButton.h"

class OrchestraInterface{
    public:
        OrchestraInterface(ctre::phoenix6::Orchestra& _orchestra, std::filesystem::path musicFolder);

        void UpdateTrackList(std::filesystem::path musicFolder);

    private:
        ctre::phoenix6::Orchestra& m_orchestraRef;

        CommandDashboardButton m_PausePlay;
        CommandDashboardButton m_StopTrack;
        frc::SendableChooser<std::filesystem::path> m_TrackSelector;
};