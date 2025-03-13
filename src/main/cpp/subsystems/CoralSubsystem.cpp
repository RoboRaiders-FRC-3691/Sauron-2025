#include "subsystems/CoralSubsystem.h"


using namespace CoralConstants;

CoralSubsystem::CoralSubsystem() : AngleMotor{kCoralAngleMotorPort, kCoralCANLoop}, IntakeMotor{kCoralIntakeMotorPort, kCoralCANLoop}, CoralCANdi{kCoralCANdiPort, kCoralCANLoop}, m_PoseRequest(0_tr), m_VelRequest(0_rpm){
    AngleMotor.GetConfigurator().Apply(kCoralAngleConfigs);
    IntakeMotor.GetConfigurator().Apply(kCoralIntakeConfigs);
}

void CoralSubsystem::Periodic(){

}

//Command that sets the coral mechanism angle
frc2::CommandPtr CoralSubsystem::SetAngle(units::angle::turn_t angle){
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

//Command that runs the intake at intakeVelocity until interupted
frc2::CommandPtr CoralSubsystem::RunIntake(units::angular_velocity::revolutions_per_minute_t intakeVelocity){
    return StartEnd(
            [this, intakeVelocity]{
                IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
            },
            [this]{
			    IntakeMotor.StopMotor();
			});
}


//Comnmand that runs the intake at intakeVelocity for "timeout" seconds when called
frc2::CommandPtr CoralSubsystem::RunIntakeFor(units::angular_velocity::revolutions_per_minute_t intakeVelocity, units::time::second_t timeout){
    return RunIntake(intakeVelocity).WithTimeout(timeout);
}

//Command that runs the intake at intakeVelocity until the coral limit switch it pressed
frc2::CommandPtr CoralSubsystem::IntakeWithSensor(units::angular_velocity::revolutions_per_minute_t intakeVelocity){
  return Run([this, intakeVelocity]{
            IntakeMotor.SetControl(m_VelRequest.WithVelocity(intakeVelocity));
			})
        .FinallyDo([this]{
			IntakeMotor.StopMotor();
			})
        .Until([this]{
			return CoralCANdi.GetS1Closed().GetValue();
      		});
}


//Returns the angle of the coral mechanism
units::turn_t CoralSubsystem::GetAngle(){
    return AngleMotor.GetPosition().GetValue();
}

//Checks if a given coral mehanism angle is within the mechanism limits *DOES NOT account for if will collid with algae arm*
bool CoralSubsystem::ValidAngle(units::degree_t angle){
    if(angle > kUpperLimit || angle < kLowerLimit){
        return false;
    }
    return true;
}

ctre::phoenix6::hardware::TalonFX& CoralSubsystem::GetAngleMotor(){
    return AngleMotor;
}

ctre::phoenix6::hardware::TalonFXS& CoralSubsystem::GetIntakeMotor(){
    return IntakeMotor;
}
