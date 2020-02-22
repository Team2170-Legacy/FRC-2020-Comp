/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "Commands/SetHoodHigh.h"
#include "Commands/SetShooterSpeed.h"
#include "Subsystems/Shooter.h"
#include "frc/Preferences.h"

class ConfigShooterHigh
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 ConfigShooterHigh> {
 public:
  ConfigShooterHigh(Shooter* subsystem);
  double shooterSpeedHigh;
};
