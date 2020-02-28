/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/VisionDriveAuto.h"

VisionDriveAuto::VisionDriveAuto(Vision* vision, DriveTrain* drive, double acceptableError, double maxTime) : m_vision{vision}, m_drive{drive} {
  	AddRequirements(vision);
   AddRequirements(drive);
   acceptableDegreeError = acceptableError;
   timeRemaining = maxTime;
}

// Called when the command is initially scheduled.
void VisionDriveAuto::Initialize() {
   m_vision->VisionSteerInit();
}

// Called repeatedly when this Command is scheduled to run
void VisionDriveAuto::Execute() {
    std::pair<double, double> result = m_vision->SteerToLockedTarget();
    m_drive->AutoVelocityArcadeDrive(result.first, result.second);
    timeRemaining -= deltaTime;
}

// Called once the command ends or is interrupted.
void VisionDriveAuto::End(bool interrupted) {
   m_vision->VisionSteerEnd();
}

// Returns true when the command should end.
bool VisionDriveAuto::IsFinished() { 
  return (timeRemaining <= 0 || abs(m_vision->GetXAngleToTarget()) <= acceptableDegreeError);
 }
