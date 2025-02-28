#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>

#include "Constants.h"

#include "subsystems/CoralSubsystem.h"
#include "subsystems/AlgaeSubsystem.h"
#include "subsystems/ElevatorSubsystem.h"

namespace ReefCommands{
    frc2::CommandPtr PlaceCoralAtLevel(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatoSubsystem, int level);
    frc2::CommandPtr RemoveAlgaeAtLevel(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatoSubsystem, int level);
}