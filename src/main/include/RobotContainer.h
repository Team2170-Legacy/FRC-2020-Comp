/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/StartEndCommand.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/WaitCommand.h>
#include "frc2/command/SequentialCommandGroup.h"
#include <frc2/command/PrintCommand.h>

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>
#include "units/units.h"

#include "Subsystems/DriveTrain.h"

#include "Commands/TeleopDrive.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

  enum Profile 
  { NoTrajectory = 0, 
    ShootFromLine_L = 1,
    ShootFromLine_R = 2, 
    ShootFromLine_C = 3,  
    ShootFromPwrPrt_L = 4,
    ShootFromPwrPrt_R = 5,
    ShootFromPwrPrt_C = 6,
    GatherMoreBalls = 7
  };

 private:
  // The robot's subsystems and commands are defined here...
  DriveTrain m_driveTrain;

  frc::SendableChooser<frc2::Command*> m_chooser;
  void ConfigureButtonBindings();

  frc::XboxController m_driver{HIDIDs::kDriver};
  frc::XboxController m_operator{HIDIDs::kOperator};
};