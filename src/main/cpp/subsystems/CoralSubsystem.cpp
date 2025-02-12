#include "subsystems/CoralSubsystem.h"


using namespace CoralConstants;

CoralSubsystem::CoralSubsystem() : AngleMotor{kCoralAngleMotor}, IntakeMotor{kCoralIntakeMotor}, m_PoseRequest(0_tr), m_VelRequest(0_rpm){
  AngleMotor.GetConfigurator().Apply(kCoralAngleConfigs);
  IntakeMotor.GetConfigurator().Apply(kCoralIntakeConfigs);
}

void CoralSubsystem::Periodic(){
  
}

frc2::CommandPtr CoralSubsystem::SetAngle(units::degree_t angle){
  return RunOnce([this, angle] {
    if(ValidAngle(angle)){
      AngleMotor.SetControl(m_PoseRequest.WithPosition(angle));
    }
  });
}

//Command that sets the intake velocity to a given value
frc2::CommandPtr CoralSubsystem::SetIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity){
  return RunOnce([this, intakeVelocity]{
	IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
  });
}

//Comnmand that runs the intake at intakeVelocity for "timeout" seconds when called
frc2::CommandPtr CoralSubsystem::RunIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity, units::time::second_t timeout){
  return RunOnce([this, intakeVelocity]{
            IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
			})
        .FinallyDo([this]{
			IntakeMotor.StopMotor();
			})
        .WithTimeout(timeout);
}

units::turn_t CoralSubsystem::GetAngle(){
  return AngleMotor.GetPosition().GetValue();
}

bool CoralSubsystem::ValidAngle(units::degree_t angle){
  if(angle > kUpperLimit || angle < kLowerLimit){
    return false;
  }
  return true;
}
