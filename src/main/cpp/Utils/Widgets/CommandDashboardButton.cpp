#include <Utils/Widgets/CommandDashboardButton.h>

CommandDashboardButton::CommandDashboardButton(std::string name) : ntTable(nt::NetworkTableInstance::GetDefault().GetTable(fmt::format("/Dashboard-Widgets/{}", name))){
    ButtonState.SetDefault(false);
}


frc2::Trigger CommandDashboardButton::GetButton(frc::EventLoop* loop){
    return frc2::Trigger(loop, [this] { return ButtonState.Get(); });
}

void CommandDashboardButton::SetState(bool newState){
    ButtonState.Set(newState);
}