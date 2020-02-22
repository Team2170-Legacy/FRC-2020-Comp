/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc2/command/InstantCommand.h"
#include "frc2/command/SequentialCommandGroup.h"

#include "frc/trajectory/Trajectory.h"
#include "frc/trajectory/TrajectoryGenerator.h"

RobotContainer::RobotContainer() {
  m_driveTrain.SetDefaultCommand(TeleopDrive(&m_driveTrain));

  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here6
  frc2::JoystickButton(&m_operator,1).WhileHeld(new IntakeOn(&m_intake));
  frc2::JoystickButton(&m_operator,2).WhileHeld(new IntakeReverse(&m_intake));
  frc2::JoystickButton(&m_operator,3).WhileHeld(new SpinStorage(&m_feeder));
  frc2::JoystickButton(&m_operator,4).WhileHeld(new SpinStorageCCW(&m_feeder));
  frc2::JoystickButton(&m_operator,5).WhileHeld(new ClimbGenUp(&m_climber));
  frc2::JoystickButton(&m_operator,6).WhileHeld(new ClimbGenDown(&m_climber));
  frc2::JoystickButton(&m_operator,7).WhileHeld(new ExtendWinch(&m_climber));
  frc2::JoystickButton(&m_operator,8).WhileHeld(new RetractWinch(&m_climber));
  frc2::JoystickButton(&m_operator,9).WhileHeld(new ConfigShooterHigh(&m_shooter));
  frc2::JoystickButton(&m_operator,10).WhileHeld(new ConfigShooterLow(&m_shooter));
  frc2::JoystickButton(&m_driver, 3).WhileHeld(new VisionDrive(&m_vision, &m_driveTrain));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {

  // Set up config for trajectory
  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed,
                               AutoConstants::kMaxAcceleration);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(DriveConstants::kDriveKinematics);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
//      {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
      {},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      config);

  frc2::RamseteCommand ramseteCommand(
    exampleTrajectory, 
    [this] {return m_driveTrain.GetPose();},
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    DriveConstants::kDriveKinematics,
    [this](auto left, auto right){m_driveTrain.SetWheelVelocity(left, right);},
    &m_driveTrain);

  // An example command will be run in autonomous
  return new frc2::SequentialCommandGroup(
    std::move(ramseteCommand),
    frc2::InstantCommand([this]{m_driveTrain.SetWheelVelocity(0.0, 0.0);}, {}));
}

void RobotContainer::StartDataLogging() {
  m_vision.EnableLogging();
  m_driveTrain.EnableLogging();
}

void RobotContainer::EndDataLogging() {
  m_vision.DisableLogging();
  m_driveTrain.DisableLogging();
}