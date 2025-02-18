#pragma once

#include <frc/GenericHID.h>
#include <wpi/array.h>

    class AdafruitMacroPad : public frc::GenericHID {
        public:
            //Construct an instance of a MacroPad. The port is the port on the Driver Station that the MacroPad is plugged into (0-5).
            AdafruitMacroPad(int port);

            ~AdafruitMacroPad() override = default;

            AdafruitMacroPad(AdafruitMacroPad&&) = default;
            AdafruitMacroPad& operator=(AdafruitMacroPad&&) = default;

            double GetKnobRotation();
            bool GetKnobButton();
            bool GetKnobButtonPressed();
            bool GetKnobButtonReleased();
            
            bool GetKey(int keyNumber);
            bool GetKey(int row, int col);

            bool GetKeyPressed(int keyNumber);
            bool GetKeyPressed(int row, int col);

            bool GetKeyReleased(int keyNumber);
            bool GetKeyReleased(int row, int col);

    };
