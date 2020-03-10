/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/LinearFilter.h>
#include "RobotContainer.h"
#include "DriveControllers/DriveController.h"
#include "Subsystems/DriveTrain.h"
#include "hwcfg.h"
#include "JoystickAdapters/JoystickConstants.h"
#include "JoystickAdapters/JoystickAdapter.h"
#include "JoystickAdapters/RawInput.h"
#include "JoystickAdapters/Deadband.h"
#include "JoystickAdapters/Exponential.h"
#include <frc/XboxController.h>

class TeleopDrive :  public frc2::CommandHelper<frc2::CommandBase, TeleopDrive> {
 public:
 enum DriveMode
  {
    ArcadeVelocity = 0,
    Cheesy = 1
  };
  DriveController* driveControllers[2]; 
  TeleopDrive(DriveTrain* subsystem, frc::XboxController *driverJoystick);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End(bool interrupted) override;

private:
  DriveTrain* m_driveTrain;
  DriveMode m_driveMode;
  JoystickAdapter* m_joystick;
};