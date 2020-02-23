/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/JostleStorage.h"

JostleStorage::JostleStorage(Feeder* subsystem): m_feeder{subsystem} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void JostleStorage::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void JostleStorage::Execute() {
  m_feeder->Agitate();
}

// Called once the command ends or is interrupted.
void JostleStorage::End(bool interrupted) {}

// Returns true when the command should end.
bool JostleStorage::IsFinished() { return false; }
