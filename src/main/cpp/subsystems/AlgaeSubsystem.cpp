#include "subsystems/AlgaeSubsystem.h"


using namespace AlgaeConstants;

AlgaeSubsystem::AlgaeSubsystem() : AngleMotor{kAlgaeAngleMotorPort, kAlgaeCANLoop}, IntakeMotor{kAlgaeIntakeMotorPort, kAlgaeCANLoop}, m_PoseRequest(0_tr), m_VelRequest(0_rpm){
    AngleMotor.GetConfigurator().Apply(kAlgaeAngleConfigs);
    IntakeMotor.GetConfigurator().Apply(kAlgaeIntakeConfigs);
}

void AlgaeSubsystem::Periodic(){

}

//Command that sets the algae mechanism angle
frc2::CommandPtr AlgaeSubsystem::SetAngle(units::degree_t angle){
    return RunOnce([this, angle] {
        if(ValidAngle(angle)){
    		AngleMotor.SetControl(m_PoseRequest.WithPosition(angle));
    }
  });
}

//Command that sets the intake velocity to a given value
frc2::CommandPtr AlgaeSubsystem::SetIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity){
    return RunOnce([this, intakeVelocity]{
        IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
  });
}

//Command that runs the intake at intakeVelocity until interupted
frc2::CommandPtr AlgaeSubsystem::RunIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity){
    return StartEnd(
            [this, intakeVelocity]{
                IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
            },
            [this]{
			    IntakeMotor.StopMotor();
			});
}


//Comnmand that runs the intake at intakeVelocity for "timeout" seconds when called
frc2::CommandPtr AlgaeSubsystem::RunIntakeFor(units::angular_velocity::revolutions_per_minute_t intakeVelocity, units::time::second_t timeout){
    return RunIntake(intakeVelocity).WithTimeout(timeout);
}

//Returns the angle of the algae mechanism
units::turn_t AlgaeSubsystem::GetAngle(){
    return AngleMotor.GetPosition().GetValue();
}

//Checks if a given algae mehanism angle is within the mechanism limits
bool AlgaeSubsystem::ValidAngle(units::degree_t angle){
    if(angle > kUpperLimit || angle < kLowerLimit){
        return false;
    }
    return true;
}
