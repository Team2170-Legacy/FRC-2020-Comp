/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ClimbGenUp.h"
#include "Robot.h"

ClimbGenUp::ClimbGenUp(Climber* subsystem): m_climber{subsystem} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void ClimbGenUp::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbGenUp::Execute() {
  m_climber->ClimberUp();
}

// Called once the command ends or is interrupted.
void ClimbGenUp::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimbGenUp::IsFinished() { return false; }
