/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TeleopDrive.h"
#include "Robot.h"

TeleopDrive::TeleopDrive(DriveTrain* subsystem) : m_driveTrain{subsystem}
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
 // Requires(Robot::driveTrain.get());
 m_driveMode = (DriveMode)frc::Preferences::GetInstance()->GetInt("Drive Type",(int)ArcadeVelocity);
 driveControllers[ArcadeVelocity] = ArcadeVelocityDrive(m_driveTrain->SetWheelVelocityPercentage, m_driveTrain->GainSelect::kDriverVelocity);
 driveControllers[Cheesy] = CheesyDrive(m_driveTrain->SetWheelVelocityPercentage, m_driveTrain->GainSelect::kDriverVelocity);
 AddRequirements({subsystem});
}

// Called just before this Command runs the first time
void TeleopDrive::Initialize() 
{
}

// Called repeatedly when this Command is scheduled to run
void TeleopDrive::Execute()
{
   double yAxis = Robot::oi->getDriverJoystick()->GetRawAxis((int)JoystickAxes::yAxis);
   double speedPos = Robot::oi->getDriverJoystick()->GetRawAxis((int)JoystickAxes::rTrigger);
   double speedNeg = Robot::oi->getDriverJoystick()->GetRawAxis((int)JoystickAxes::lTrigger);

   double turn_rate = speedPos - speedNeg;

   printf("Calling Set Motor Commands \n");
   driveControllers[m_driveMode].SetMotorCommands(m_driveTrain, yAxis, turn_rate);
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDrive::IsFinished() { 
  return false; 
  }

// Called once after isFinished returns true
void TeleopDrive::End(bool interrupted) 
 {

 }

