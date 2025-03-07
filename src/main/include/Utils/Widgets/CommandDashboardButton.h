#pragma once

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/BooleanTopic.h>
#include <networktables/DoubleTopic.h>
#include <networktables/StringTopic.h>

#include <frc2/command/button/Trigger.h>

class CommandDashboardButton{
    public:
        CommandDashboardButton(std::string name);
    
        frc2::Trigger GetButton(
                            frc::EventLoop* loop = frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop());

        void SetState(bool newState);

    private:
        std::shared_ptr<nt::NetworkTable> ntTable;
        nt::BooleanEntry ButtonState;
};