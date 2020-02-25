/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/TeleopDrive.h"
#include "Robot.h"

#define xAxis_Rate_Max  0.04
#define turn_Rate_Max   0.05

TeleopDrive::TeleopDrive(DriveTrain* subsystem) : m_driveTrain{subsystem} {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
 // Requires(Robot::driveTrain.get());
 AddRequirements({subsystem});
}

// Called just before this Command runs the first time
void TeleopDrive::Initialize() 
{
	xAxis_prev 	    = 0.0;
  turn_Rate_prev   = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void TeleopDrive::Execute()
{
  double xAxis = Robot::oi->getDriverJoystick()->GetRawAxis(1);

  double delta_xAxis = xAxis - xAxis_prev;

  if ( delta_xAxis > xAxis_Rate_Max ) {
	    xAxis_prev 	= xAxis_prev +  xAxis_Rate_Max;
  }
  else if ( delta_xAxis < xAxis_Rate_Max ) {
 	    xAxis_prev 	= xAxis_prev - xAxis_Rate_Max;
  }
  else {
      xAxis_prev 	= xAxis;
  };

  //double yAxis = Robot::oi->getDriverJoystick()->GetRawAxis(4);

  double speedPos = Robot::oi->getDriverJoystick()->GetRawAxis(3);
  double speedNeg = Robot::oi->getDriverJoystick()->GetRawAxis(2);

  double turn_Rate = 0.0;

  if (speedNeg > 0.05) {
    turn_Rate = -speedNeg;
  }
  else if (speedPos > 0.05) {
    turn_Rate = speedPos;
  }
  else {
    turn_Rate = 0.0;
  }

  double delta_turn_Rate = turn_Rate - turn_Rate_prev;

  if ( delta_turn_Rate > turn_Rate_Max ) {
    turn_Rate_prev = turn_Rate_prev + turn_Rate_Max;
  }
  else if ( delta_turn_Rate < turn_Rate_Max ) {
    turn_Rate_prev = turn_Rate_prev - turn_Rate_Max;
  }   
  else {
    turn_Rate_prev = turn_Rate;
  };


  m_driveTrain->VelocityArcadeDrive(-xAxis_prev, -turn_Rate, true);
 // Robot::driveTrian->VelocityArcadeDrive(turnRate, yAxis, true);
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDrive::IsFinished() { 
  return false; 
  }

// Called once after isFinished returns true
void TeleopDrive::End(bool interrupted) 
 {
      xAxis_prev      = 0.0;
      turn_Rate_prev  = 0.0;
 }