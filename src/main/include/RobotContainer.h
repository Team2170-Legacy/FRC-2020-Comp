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

#include "frc/trajectory/Trajectory.h"
#include "frc/trajectory/TrajectoryGenerator.h"

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>
#include "units/units.h"

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
#include "Commands/ConfigShooterHigh.h"
#include "Commands/ConfigShooterLow.h"
#include "Commands/SetShooterSpeed.h"
#include "Commands/JostleStorage.h"
#include "Commands/FeederOff.h"
#include "Commands/LoaderDown.h"
#include "Commands/LoaderOff.h"
#include "Commands/LoaderUp.h"
#include "Commands/PullIntakeDown.h"
#include "Commands/PullIntakeUp.h"
#include "Commands/ShooterOff.h"
#include "Commands/TeleopIntake.h"
#include "Commands/WaitForShooterSpeed.h"
#include "Commands/AutonomousMotionProfile.h"
#include "Commands/VisionDrive.h"
#include "Commands/VisionDriveAuto.h"
#include "Commands/ExtendWinch.h"
#include "Commands/RetractWinch.h"

#include "hwcfg.h"
#include "Constants.h"

#include "Automoves/To_PwrPort_C.h"
#include "Automoves/To_PwrPort_L.h"
#include "Automoves/To_PwrPort_R.h"
#include "Automoves/To_Trench_C.h"
#include "Automoves/To_Trench_L.h"
#include "Automoves/To_Trench_R.h"
#include "Automoves/Backwards_Long.h"
#include "Automoves/Backwards_Short.h"

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

  frc::SendableChooser<frc2::Command*> m_chooser;
  frc::SendableChooser<Profile> m_trajectoryChooser;
  frc::SendableChooser<double> m_delayChooser;

  frc2::Command* GenerateRamseteCommand();
  void ConfigureButtonBindings();

  AutonomousCommand m_autonomousCommand;

  frc::XboxController m_driver{HIDIDs::kDriver};
  frc::XboxController m_operator{HIDIDs::kOperator};

  // Climber related commands
  frc2::InstantCommand m_RetractWinch{[this] {m_climber.WinchRetract();}, {&m_climber}};
  frc2::InstantCommand m_StopWinch{[this] {m_climber.WinchStop();}, {&m_climber}};
  frc2::ParallelRaceGroup m_ReleaseClimber = 
    frc2::StartEndCommand(
      [this] {m_climber.WinchRetract();}, 
      [this] {m_climber.WinchStop();}, {&m_climber}).WithTimeout(1.0_s);

  frc2::StartEndCommand m_ReleaseInterlock {[this] {m_climber.ReleaseInterlock();},
                    {[this] {m_climber.SetInterlock();}}, {&m_climber}};

  // Shooter related commands
   frc2::ParallelRaceGroup m_WaitShooterSpeed = 
     frc2::WaitCommand(3.0_s).WithInterrupt([this] {return m_shooter.ShooterAtSpeed();});

  frc2::SequentialCommandGroup m_TestGroup{frc2::WaitCommand(3.0_s), frc2::WaitCommand(38.0_s)};
  frc2::InstantCommand m_InstantSpinStorageCCW{[this] {m_feeder.RotateCCW(); }, {&m_feeder}};
  frc2::InstantCommand m_StopSpinStorageCCW{[this] {m_feeder.FeedStop(); }, {&m_feeder}};

};
