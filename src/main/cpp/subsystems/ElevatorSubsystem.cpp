#include "subsystems/ElevatorSubsystem.h"


using namespace ElevatorConstants;

ElevatorSubsystem::ElevatorSubsystem() : RightMotor{kElevatorMotorRightPort, kElevatorCANLoop}, LeftMotor{kElevatorMotorLeftPort, kElevatorCANLoop}, m_Request(0_tr){
  RightMotor.GetConfigurator().Apply(kElevatorMotorConfigs);
  LeftMotor.SetControl(ctre::phoenix6::controls::Follower{kElevatorMotorRightPort, true});
}

void ElevatorSubsystem::Periodic(){
  
}

units::inch_t ElevatorSubsystem::RotationsToHeight(units::turn_t turns){
  return units::inch_t(turns.value()*kInPerRot);
}

units::turn_t ElevatorSubsystem::HeightToRotations(units::inch_t height){
  return units::turn_t(height.value()/kInPerRot);
}

frc2::CommandPtr ElevatorSubsystem::SetHeight(units::inch_t height){
  return RunOnce([this, height] {
    if(ValidHeight(height)){
      RightMotor.SetControl(m_Request.WithPosition(HeightToRotations(height)));
    }
  });
}

units::inch_t ElevatorSubsystem::GetHeight(){
  return RotationsToHeight(RightMotor.GetPosition().GetValue());
}

bool ElevatorSubsystem::ValidHeight(units::inch_t height){
  if(height > kUpperLimit || height < kLowerLimit){
    return false;
  }
  return true;
}