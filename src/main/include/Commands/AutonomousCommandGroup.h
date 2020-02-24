/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "ProfileData.h"
#include "Commands/AutonomousMotionProfile.h"
#include "frc/Preferences.h"
#include "Subsystems/DriveTrain.h"


class AutonomousCommandGroup
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutonomousCommandGroup> {
 public:
  AutonomousCommandGroup(double delay, DriveTrain* m_driveTrain, const ProfileData *leftProfile, 
        const ProfileData *rightProfile);

 private:
  DriveTrain* m_driveTrain;
  double delay;
};
