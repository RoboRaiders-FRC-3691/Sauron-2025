#include "subsystems/ClimberSubsystem.h"


using namespace ClimberConstants;

ClimberSubsystem::ClimberSubsystem() : ClimbMotor{kClimberMotorPort, kClimberCANLoop}, m_PoseRequest(0_tr){
    ClimbMotor.GetConfigurator().Apply(kClimberMotorConfigs);
}

void ClimberSubsystem::Periodic(){
  
}

//sets angle of the climber arm
frc2::CommandPtr ClimberSubsystem::SetAngle(units::angle::turn_t angle){
    return RunOnce([this, angle] {
        if(ValidAngle(angle)){
            ClimbMotor.SetControl(m_PoseRequest.WithPosition(angle));
        }
    });
}


bool ClimberSubsystem::ValidAngle(units::angle::turn_t angle){
    if(angle > kUpperLimit || angle < kLowerLimit){
        return false;
    }
    return true;
}

ctre::phoenix6::hardware::TalonFX& ClimberSubsystem::GetClimbMotor(){
    return ClimbMotor;
}