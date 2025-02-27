#include <CommandGroups/ReefCommands.h>

frc2::CommandPtr ReefCommands::PlaceCoralAtLevel(CoralSubsystem &_CoralSubsystem, ElevatorSubsystem &_ElevatoSubsystem, int level){
    return _ElevatoSubsystem.SetHeight(CoralConstants::kCoralPlacementHeights[level]).AndThen(
           _CoralSubsystem.SetAngle(CoralConstants::kCoralPlacementAngles[level]));
           //_CoralSubsystem.RunIntakeFor(CoralConstants::kCoralPlacementVelocity, CoralConstants::kCoralPlacementTime));
}

frc2::CommandPtr ReefCommands::RemoveAlgaeAtLevel(AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatoSubsystem, int level){
    return _ElevatoSubsystem.SetHeight(AlgaeConstants::kAlgaePlacementHeights[level]).AndThen(
           _AlgaeSubsystem.SetAngle(AlgaeConstants::kAlgaePlacementAngles[level])).AndThen(
           _AlgaeSubsystem.RunIntakeFor(AlgaeConstants::kAlgaePlacementVelocity, AlgaeConstants::kAlgaePlacementTime));
}