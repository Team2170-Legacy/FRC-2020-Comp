/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutonomousMotionProfile.h"

AutonomousMotionProfile::AutonomousMotionProfile(DriveTrain* subsystem, const ProfileData* leftProfile, const ProfileData* rightProfile) : m_driveTrain{subsystem} {
  // Use addRequirements() here to declare subsystem dependencies.
  LeftProfile = leftProfile;
  RightProfile = rightProfile;
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void AutonomousMotionProfile::Initialize() {
  rowIndex = 0;
}

// Called repeatedly when this Command is scheduled to run
void AutonomousMotionProfile::Execute() {
  double leftVelocity = LeftProfile->at(rowIndex).at(1);
  double rightVelocity = RightProfile->at(rowIndex).at(1);
  m_driveTrain->SetWheelVelocity(leftVelocity, rightVelocity);
  rowIndex++;
}

// Called once the command ends or is interrupted.
void AutonomousMotionProfile::End(bool interrupted) {}

// Returns true when the command should end.
bool AutonomousMotionProfile::IsFinished() { return false; }
