/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TeleopDrive.h"
//#include "Robot.h"

TeleopDrive::TeleopDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void TeleopDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TeleopDrive::Execute() {
  double xAxis = Robot::oi->getDriverJoystick()->GetRawAxis(1);
  double yAxis = Robot::oi->getDriverJoystick()->GetRawAxis(4);

  double speedPos = Robot::oi->getDriverJoystick()->GetRawAxis(3);
  double speedNeg = Robot::oi->getDriverJoystick()->GetRawAxis(2);

  double speedVoltage = 0.0;
  double speedVelocity = 0.0;

  Robot::driveTrain->VelocityArcadeDrive(-xAxis, -yAxis, true);
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDrive::IsFinished() { 
  return false; 
  }

// Called once after isFinished returns true
void TeleopDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopDrive::Interrupted() {}