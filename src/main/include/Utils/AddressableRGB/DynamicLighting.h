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
            // DynamicLighting constructor
            DynamicLighting(int port, int length);

            // Returns a command that sets the LED effect
            frc2::CommandPtr SetEffect(frc::LEDPattern effect, bool loopingEffect);

            // Returns a command that sets the LED effect
            frc2::CommandPtr SetEffect(frc::LEDPattern effect, bool loopingEffect, units::time::second_t timeout);

            // Returns a command that clears effects from the LED(s)
            frc2::CommandPtr ClearEffect();

            // Notes:
            // Didnt derive from subsystem base due to use across multiple subsystems
            // Currently Quite Bear Bones
            // Could implement fun capability such as the ability for a strip to display a scale from a float or something similar
            // Could also implement support for LED strips vs LED array assuming they are wired in the same way

        private:
            // Create a buffer to hold the LEDData for each LED
            std::vector<frc::AddressableLED::LEDData> m_LEDBuffer;
    };
}

