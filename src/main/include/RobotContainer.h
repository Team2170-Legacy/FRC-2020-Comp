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

#include "Subsystems/Climber.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Feeder.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Loader.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Vision.h"

#include "Commands/AutonomousCommand.h"
#include "Commands/TeleopDrive.h"
#include "Commands/IntakeOn.h"
#include "Commands/IntakeReverse.h"
#include "Commands/SpinStorage.h"
#include "Commands/SpinStorageCCW.h"
#include "Commands/VisionDrive.h"
#include "Commands/ConfigShooterHigh.h"
#include "Commands/ConfigShooterLow.h"
#include "Commands/SetShooterSpeed.h"


#include "frc/XboxController.h"
#include "Commands/ClimbGenUp.h"
#include "Commands/ClimbGenDown.h"
#include "Commands/ExtendWinch.h"
#include "Commands/RetractWinch.h"
#include "hwcfg.h"
#include "Constants.h"

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

  void StartDataLogging(void);
  void EndDataLogging(void);

 private:
  // The robot's subsystems and commands are defined here...
  DriveTrain m_driveTrain;
  Intake m_intake;
  Climber m_climber;
  Vision m_vision;
  Shooter m_shooter;
  Feeder m_feeder;
  Loader m_loader;

  AutonomousCommand m_autonomousCommand;

  frc::XboxController m_driver{HIDIDs::kDriver};
  frc::XboxController m_operator{HIDIDs::kOperator};

  void ConfigureButtonBindings();
};
