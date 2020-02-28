/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "Subsystems/Shooter.h"
#include "Subsystems/Vision.h"
#include "Subsystems/Loader.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Feeder.h"

#include "units/units.h"

class AimFireShooter
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AimFireShooter> {
 public:
  AimFireShooter(Shooter* shooter, Vision* vision, Loader* loader, DriveTrain* drivetrain, Feeder* feeder);

private:
  //Vision config parameters
  const double kVisionDriveAcceptableError = 0.8; // VisionDrives during auto will terminate once they reach this error or less
  const double kMaxVisionDriveTime = 3.0; // VisionDrives during auto will terminate if they take longer than this time
  const units::second_t kAutoShootTime;
};
