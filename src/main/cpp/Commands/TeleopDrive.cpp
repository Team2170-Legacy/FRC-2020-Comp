/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TeleopDrive.h"
#include "Robot.h"

TeleopDrive::TeleopDrive(DriveTrain* subsystem, frc::XboxController *driverJoystick) : m_driveTrain{subsystem}
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
 // Requires(Robot::driveTrain.get());
 //m_joystick = new Deadband(new RawInput(Robot::oi->getDriverJoystick()),deadband_limit);
 m_joystick = new Exponential(new Deadband(new RawInput(driverJoystick), deadband_limit), joystick_exponent);
 m_driveMode = (DriveMode)frc::Preferences::GetInstance()->GetInt("Drive Type",(int)ArcadeVelocity);
 driveControllers[ArcadeVelocity] = new ArcadeVelocityDrive(m_driveTrain->SetWheelVelocityPercentage, m_driveTrain->GainSelect::kDriverVelocity);
 driveControllers[Cheesy] = new CheesyDrive(m_driveTrain->SetWheelVelocityPercentage, m_driveTrain->GainSelect::kDriverVelocity);
 AddRequirements({subsystem});
}

// Called just before this Command runs the first time
void TeleopDrive::Initialize() 
{
}

// Called repeatedly when this Command is scheduled to run
void TeleopDrive::Execute()
{
   double yAxis = m_joystick->GetRawAxis((int)JoystickAxes::yAxis);
   double speedPos = m_joystick->GetRawAxis((int)JoystickAxes::rTrigger);
   double speedNeg = m_joystick->GetRawAxis((int)JoystickAxes::lTrigger);

   double turn_rate = speedPos - speedNeg;

   printf("Calling Set Motor Commands \n");
   driveControllers[m_driveMode]->SetMotorCommands(m_driveTrain, yAxis, turn_rate);
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDrive::IsFinished() { 
  return false; 
  }

// Called once after isFinished returns true
void TeleopDrive::End(bool interrupted) 
 {

 }

