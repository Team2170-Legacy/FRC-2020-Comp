/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "Commands/AutonomousCommandGroup.h"
#include "Commands/AutonomousMotionProfile.h"
#include "Commands/WaitCommand.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
AutonomousCommandGroup::AutonomousCommandGroup(double delay, DriveTrain* m_driveTrain, const ProfileData *leftProfile, 
        const ProfileData *rightProfile) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands(WaitCommand(delay), AutonomousMotionProfile(m_driveTrain, leftProfile, rightProfile));
}
