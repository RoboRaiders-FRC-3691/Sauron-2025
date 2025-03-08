#pragma once

#include <functional>

#include <units/time.h>

#include <frc2/command/Command.h>
#include <frc2/command/Commands.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandScheduler.h>

#include <frc/AddressableLED.h>
#include <frc/LEDPattern.h>


namespace AddressableRGB{

    class DynamicLighting : public frc::AddressableLED{
        public:
            DynamicLighting(int port, int length);

            frc2::CommandPtr SetEffect(frc::LEDPattern effect, bool loopingEffect);

            frc2::CommandPtr SetEffect(frc::LEDPattern effect, bool loopingEffect, units::time::second_t timeout);

            frc2::CommandPtr ClearEffect();

            //Didnt derive from subsystem base due to use across multiple subsystems
            //Currently Quite Bear Bones
            //Could implement fun capability such as the ability for a strip to display a scale from a float or something similar
            //Could also implement support for LED strips vs LED array assuming they are wired in the same way

        private:
            std::vector<frc::AddressableLED::LEDData> m_LEDBuffer;
    };
}

