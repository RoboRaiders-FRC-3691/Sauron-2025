#include <CommandGroups/ReefCommands.h>

frc2::CommandPtr ReefCommands::PlaceCoralAtLevel(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatorSubsystem, int level){
    return _ElevatorSubsystem.SetHeight(CoralConstants::kCoralPlacementHeights[level]).AndThen(
           _CoralSubsystem.SetAngle(CoralConstants::kCoralPlacementCoralAngles[level])).AndThen(
           _AlgaeSubsystem.SetAngle(CoralConstants::kCoralPlacementAlgaeAngles[level]));
           //_CoralSubsystem.RunIntakeFor(CoralConstants::kCoralPlacementVelocity, CoralConstants::kCoralPlacementTime));
}

frc2::CommandPtr ReefCommands::RemoveAlgaeAtLevel(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatorSubsystem, int level){
    return _ElevatorSubsystem.SetHeight(AlgaeConstants::kAlgaeRemovalHeights[level]).AndThen(
           _CoralSubsystem.SetAngle(AlgaeConstants::kAlgaeRemovalCoralAngles[level])).AndThen(
           _AlgaeSubsystem.SetAngle(AlgaeConstants::kAlgaeRemovalAlgaeAngles[level]));
           //_AlgaeSubsystem.RunIntakeFor(AlgaeConstants::kAlgaeRemovalVelocity, AlgaeConstants::kAlgaeRemovalTime));
}

frc2::CommandPtr ReefCommands::AlgaeProcessor(CoralSubsystem &_CoralSubsystem, AlgaeSubsystem &_AlgaeSubsystem, ElevatorSubsystem &_ElevatorSubsystem){
    return _ElevatorSubsystem.SetHeight(AlgaeConstants::kAlgaeProcessorHeight).AndThen(
           _CoralSubsystem.SetAngle(AlgaeConstants::kAlgaeProcessorCoralAngle)).AndThen(
           _AlgaeSubsystem.SetAngle(AlgaeConstants::kAlgaeProcessorAlgaeAngle));
}