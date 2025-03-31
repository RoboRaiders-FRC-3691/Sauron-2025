#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>

#include "Constants.h"

#include "subsystems/CoralSubsystem.h"
#include "subsystems/AlgaeSubsystem.h"
#include "subsystems/ElevatorSubsystem.h"

namespace ReefCommands{

    // Returns a sequence of commands as an frc2::CommandPtr that uses predifined constants in order to prepare the coral, algae, and elevator subsystems for a coral placement at a given level
    frc2::CommandPtr PlaceCoralAtLevel(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatorSubsystem, int level);

    // Returns a sequence of commands as an frc2::CommandPtr that uses predifined constants in order to prepare the coral, algae, and elevator subsystems for a algae removal at a given level
    frc2::CommandPtr RemoveAlgaeAtLevel(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatorSubsystem, int level);

    // Returns a sequence of commands as an frc2::CommandPtr that uses predifined constants in order to prepare the coral, algae, and elevator subsystems for algae processor placement.
    frc2::CommandPtr AlgaeProcessor(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatorSubsystem);
}