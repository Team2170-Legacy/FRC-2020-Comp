/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/WaitCommand.h"

WaitCommand::WaitCommand(double delay) {
  // Use addRequirements() here to declare subsystem dependencies.
  timeRemaining = delay;
}

// Called when the command is initially scheduled.
void WaitCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WaitCommand::Execute() {
  timeRemaining -= deltaTime;
}

// Called once the command ends or is interrupted.
void WaitCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool WaitCommand::IsFinished() { 
    return (timeRemaining <= 0);
  }
