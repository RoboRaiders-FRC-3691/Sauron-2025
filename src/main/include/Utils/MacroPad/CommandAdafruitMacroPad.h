#pragma once

#include <frc/GenericHID.h>
#include <wpi/array.h>

#include "Utils/MacroPad/AdafruitMacroPad.h"

#include <frc2/command/button/Trigger.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/button/CommandGenericHID.h>

    class CommandAdafruitMacroPad : public frc2::CommandGenericHID {
        public:
            //Construct an instance of a MacroPad. The port is the port on the Driver Station that the MacroPad is plugged into (0-5).
            CommandAdafruitMacroPad(int port);

            //Get the underlying GenericHID object.
            AdafruitMacroPad& GetHID();

            double GetKnobRotation();
            frc2::Trigger GetKnobButton(
                                    frc::EventLoop* loop = frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop());
            
            frc2::Trigger GetKey(int keyNumber, 
                                    frc::EventLoop* loop = frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop());
            frc2::Trigger GetKey(int row, int col,
                                    frc::EventLoop* loop = frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop());
        private:
            AdafruitMacroPad m_hid;

    };
    

