/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ClimbGenDown.h"
#include "Robot.h"

ClimbGenDown::ClimbGenDown(Climber* subsystem): m_climber{subsystem} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void ClimbGenDown::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbGenDown::Execute() {
  m_climber->ClimberDown();
}

// Called once the command ends or is interrupted.
void ClimbGenDown::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimbGenDown::IsFinished() { return false; }
