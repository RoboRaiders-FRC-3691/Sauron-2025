#include "Utils/AddressableRGB/DynamicLighting.h"



AddressableRGB::DynamicLighting::DynamicLighting(int port, int length) : frc::AddressableLED(port){
    frc::AddressableLED::SetLength(length);
    m_LEDBuffer.resize(length);
    frc::AddressableLED::Start();
}

frc2::CommandPtr AddressableRGB::DynamicLighting::SetEffect(frc::LEDPattern effect, bool loopingEffect){
    if(loopingEffect){
        return frc2::cmd::Run([this, effect]{ effect.ApplyTo(m_LEDBuffer); }).Until([this, loopingEffect] { return !loopingEffect; });
    }
    else{
        return frc2::cmd::RunOnce([this, effect]{ effect.ApplyTo(m_LEDBuffer); });
    }
}

frc2::CommandPtr AddressableRGB::DynamicLighting::SetEffect(frc::LEDPattern effect, bool loopingEffect, units::time::second_t timeout){
    if(loopingEffect){
        return frc2::cmd::Run([this, effect]{ effect.ApplyTo(m_LEDBuffer); }).Until([this, loopingEffect] { return !loopingEffect; }).WithTimeout(timeout);
    }
    else{
        return frc2::cmd::RunOnce([this, effect]{ effect.ApplyTo(m_LEDBuffer); });
    }
}

frc2::CommandPtr AddressableRGB::DynamicLighting::ClearEffect(){
    return frc2::cmd::RunOnce([this]{ 
        frc::LEDPattern::Solid(frc::Color::kBlack);
    });
}
