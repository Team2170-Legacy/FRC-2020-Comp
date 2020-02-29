/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "Subsystems/Vision.h"
#include "Subsystems/DriveTrain.h"
/**
 * The same thing as VisionDrive, but to be used in autonomous.
 *
 * <p> This command differs from VisionDrive in that it terminates automatically, either
 * after a certain period of time or after the robot has reached an acceptable alignment error.
 * The other VisionDrive never finishes, will only terminate if interrupted, and should only be
 * used in Teleop. This is the command that should be used in the autonomous phase. 
 * 
 */
class VisionDriveAuto
    : public frc2::CommandHelper<frc2::CommandBase, VisionDriveAuto> {
 public:
  VisionDriveAuto(Vision* vision, DriveTrain* drive, double acceptableError);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
	Vision* m_vision;
	DriveTrain* m_drive;
    double acceptableDegreeError;
};
