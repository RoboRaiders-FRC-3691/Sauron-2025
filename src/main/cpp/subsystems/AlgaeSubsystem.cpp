#include "subsystems/AlgaeSubsystem.h"


using namespace AlgaeConstants;

AlgaeSubsystem::AlgaeSubsystem() : AngleMotor{kAlgaeAngleMotorPort, kAlgaeCANLoop}, IntakeMotor{kAlgaeIntakeMotorPort, kAlgaeCANLoop}, m_PoseRequest(0_tr), m_VelRequest(0_rpm){
    AngleMotor.GetConfigurator().Apply(kAlgaeAngleConfigs);
    IntakeMotor.GetConfigurator().Apply(kAlgaeIntakeConfigs);
}

void AlgaeSubsystem::Periodic(){

}

frc2::CommandPtr AlgaeSubsystem::SetAngle(units::angle::turn_t angle){
    return RunOnce([this, angle] {
        if(ValidAngle(angle)){
    		AngleMotor.SetControl(m_PoseRequest.WithPosition(angle));
    }
  });
}

frc2::CommandPtr AlgaeSubsystem::SetIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity){
    return RunOnce([this, intakeVelocity]{
        IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
  });
}

frc2::CommandPtr AlgaeSubsystem::RunIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity){
    return StartEnd(
            [this, intakeVelocity]{
                IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
            },
            [this]{
			    IntakeMotor.StopMotor();
			});
}



frc2::CommandPtr AlgaeSubsystem::RunIntakeFor(units::angular_velocity::revolutions_per_minute_t intakeVelocity, units::time::second_t timeout){
    return RunIntake(intakeVelocity).WithTimeout(timeout);
}


units::turn_t AlgaeSubsystem::GetAngle(){
    return AngleMotor.GetPosition().GetValue();
}

bool AlgaeSubsystem::ValidAngle(units::degree_t angle){
    if(angle > kUpperLimit || angle < kLowerLimit){
        return false;
    }
    return true;
}

ctre::phoenix6::hardware::TalonFX& AlgaeSubsystem::GetAngleMotor(){
    return AngleMotor;
}

ctre::phoenix6::hardware::TalonFXS& AlgaeSubsystem::GetIntakeMotor(){
    return IntakeMotor;
}