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
#include "frc/smartdashboard/SmartDashboard.h"


#include "Commands/AutonomousCommandGroup.h"

RobotContainer::RobotContainer() {
  m_driveTrain.SetDefaultCommand(TeleopDrive(&m_driveTrain));
  m_intake.SetDefaultCommand(TeleopIntake(&m_intake));

  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Chooser Setup
  m_chooser.SetDefaultOption("RamSete Command", GenerateRamseteCommand());
  m_chooser.AddOption("Matlab Auto Test", new AutonomousCommandGroup(0, &m_driveTrain));
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here6
  frc2::JoystickButton(&m_operator,1).WhileHeld(new JostleStorage(&m_feeder));
  frc2::JoystickButton(&m_operator,2).WhileHeld(new FeederOff(&m_feeder));

  frc2::JoystickButton(&m_operator,3).WhileHeld(new SpinStorage(&m_feeder));
  frc2::JoystickButton(&m_operator,4).WhileHeld(new SpinStorageCCW(&m_feeder));

  frc2::JoystickButton(&m_operator,5).WhileHeld(new ClimbGenDown(&m_climber));
  frc2::JoystickButton(&m_operator,6).WhileHeld(new ShooterOff(&m_shooter));

  frc2::JoystickButton(&m_operator, 7).WhileHeld(new PullIntakeUp(&m_intake));
  frc2::JoystickButton(&m_operator, 8).WhileHeld(new PullIntakeUp(&m_intake));

  frc2::JoystickButton(&m_operator,9).WhileHeld(new ConfigShooterHigh(&m_shooter, &m_feeder));
  frc2::JoystickButton(&m_operator,10).WhileHeld(new ConfigShooterLow(&m_shooter, &m_feeder));

  frc2::JoystickButton(&m_driver,2).WhileHeld(new LoaderOff(&m_loader));
  frc2::JoystickButton(&m_driver,3).WhileHeld(new LoaderUp(&m_loader));
  frc2::JoystickButton(&m_driver,4).WhileHeld(new LoaderDown(&m_loader));


  frc2::JoystickButton(&m_driver, 1).WhileHeld(new VisionDrive(&m_vision, &m_driveTrain));
}

frc2::Command* RobotContainer::GenerateRamseteCommand() {

  // Set up config for trajectory
  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed,
                               AutoConstants::kMaxAcceleration);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(DriveConstants::kDriveKinematics);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
     
     {frc::Translation2d(1_m, 0_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      config);

     frc::SmartDashboard::PutNumber("Trajectory Time", units::unit_cast<double>(exampleTrajectory.TotalTime()));
     t_states = exampleTrajectory.States();

  frc2::RamseteCommand ramseteCommand(
    exampleTrajectory, 
    [this] {return m_driveTrain.GetPose();},
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    DriveConstants::kDriveKinematics,
    [this](auto left, auto right){m_driveTrain.SetWheelVelocity(left, right);},
    {&m_driveTrain});

  // An example command will be run in autonomous
  return new frc2::SequentialCommandGroup(
    std::move(ramseteCommand),
    frc2::InstantCommand([this]{m_driveTrain.SetWheelVelocity(0.0, 0.0);}, {}));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  return m_chooser.GetSelected();
}

void RobotContainer::StartDataLogging() {
  m_vision.EnableLogging();
  m_driveTrain.EnableLogging();
  m_shooter.EnableLogging();
}

void RobotContainer::EndDataLogging() {
  m_vision.DisableLogging();
  m_driveTrain.DisableLogging();
  m_shooter.DisableLogging();
}