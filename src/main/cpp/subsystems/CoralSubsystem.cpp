#include "subsystems/CoralSubsystem.h"


using namespace CoralConstants;

CoralSubsystem::CoralSubsystem() : AngleMotor{kCoralAngleMotor}, IntakeMotor{kCoralIntakeMotor}, m_Request(0_tr){
  AngleMotor.GetConfigurator().Apply(kCoralAngleConfigs);
  IntakeMotor.GetConfigurator().Apply(kCoralIntakeConfigs);
}

void CoralSubsystem::Periodic(){
  
}

frc2::CommandPtr CoralSubsystem::SetAngle(units::degree_t angle){
  return RunOnce([this, angle] {
    if(ValidAngle(angle)){
      AngleMotor.SetControl(m_Request.WithPosition(angle));
    }
  });
}

units::turn_t CoralSubsystem::GetAngle(){
  return AngleMotor.GetPosition().GetValue();
}

bool CoralSubsystem::ValidAngle(units::degree_t angle){
  if(height > kUpperLimit || height < kLowerLimit){
    return false;
  }
  return true;
}