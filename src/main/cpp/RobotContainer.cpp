/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/smartdashboard/SmartDashboard.h"

#include "Commands/AimFireShooter.h"
#include "Commands/AutoSetShootHigh.h"
#include "Commands/AutoSetShootLow.h"
#include "Commands/FireShooter.h"

RobotContainer::RobotContainer() :
  kHighShooterSpeed {frc::Preferences::GetInstance()->GetDouble("High Shooter Speed", 20.0)},
  kLowShooterSpeed {frc::Preferences::GetInstance()->GetDouble("Low Shooter Speed", 20.0)},
  kAutoShootTime {(units::second_t)frc::Preferences::GetInstance()->GetDouble("Auto Shoot Time", 2.0)}
{
  std::cout << ("Setting Default Command to TeleopDrive") << std::endl;
  m_driveTrain.SetDefaultCommand(TeleopDrive(&m_driveTrain, &m_driver));
  m_intake.SetDefaultCommand(TeleopIntake(&m_intake));

  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Chooser Setup
  //  m_chooser.SetDefaultOption("RamSete Command", GenerateRamseteCommand());
  // m_chooser.AddOption("Matlab Auto Test", new AutonomousCommandGroup(0, &m_driveTrain));
  // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_trajectoryChooser.SetDefaultOption("A. No Trajectory", NoTrajectory);
  m_trajectoryChooser.AddOption("B. Shoot from Line: Start Left", ShootFromLine_L);
  m_trajectoryChooser.AddOption("C. Shoot from Line: Start Right", ShootFromLine_R);
  m_trajectoryChooser.AddOption("D. Shoot from Line: Start Center", ShootFromLine_C);
  m_trajectoryChooser.AddOption("E. Shoot from PowerPort: Start Left", ShootFromPwrPrt_L);
  m_trajectoryChooser.AddOption("F. Shoot from PowerPort: Start Right", ShootFromPwrPrt_R);
  m_trajectoryChooser.AddOption("G. Shoot from PowerPort: Start Center", ShootFromPwrPrt_C);
  //m_trajectoryChooser.AddOption("I. Gather more balls", ToPwrPort);
  frc::SmartDashboard::PutData("Auto Trajectories", &m_trajectoryChooser);

  // set-up delay chooser
  m_delayChooser.SetDefaultOption("0/No Delay", 00);
  m_delayChooser.AddOption("01 Second", 1);
  m_delayChooser.AddOption("02 Seconds", 2);
  m_delayChooser.AddOption("03 Seconds", 3);
  m_delayChooser.AddOption("04 Seconds", 4);
  m_delayChooser.AddOption("05 Seconds", 5);
  m_delayChooser.AddOption("06 Seconds", 6);
  m_delayChooser.AddOption("07 Seconds", 7);
  m_delayChooser.AddOption("08 Seconds", 8);
  m_delayChooser.AddOption("09 Seconds", 9);
  m_delayChooser.AddOption("10 Seconds", 10);
  frc::SmartDashboard::PutData("Auto Start Delay", &m_delayChooser);
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here6
  frc2::JoystickButton(&m_operator,(int)OperatorButtons::A).WhenPressed(&m_Agitate); // A
  frc2::JoystickButton(&m_operator,(int)OperatorButtons::B).WhileHeld(new FeederOff(&m_feeder)); // B

  frc2::JoystickButton(&m_operator,(int)OperatorButtons::X).WhileHeld(new SpinStorage(&m_feeder)); // X
  frc2::JoystickButton(&m_operator,(int)OperatorButtons::Y).WhileHeld(new SpinStorageCCW(&m_feeder)); // Y

  frc2::JoystickButton(&m_driver,(int)DriverButtons::LB).WhileHeld(new RetractWinch(&m_climber)); // LB
  frc2::JoystickButton(&m_operator,(int)OperatorButtons::RB).WhileHeld(new ShooterOff(&m_shooter)); // RB

  frc2::JoystickButton(&m_operator, (int)OperatorButtons::LA).WhileHeld(new PullIntakeDown(&m_intake)); // LA
  frc2::JoystickButton(&m_operator, (int)OperatorButtons::RA).WhileHeld(new PullIntakeUp(&m_intake)); // RA

  frc2::JoystickButton(&m_operator,(int)OperatorButtons::LJ_Press).WhileHeld(new ConfigShooterHigh(&m_shooter, &m_feeder)); // LJ
  frc2::JoystickButton(&m_operator,(int)OperatorButtons::RJ_Press).WhileHeld(new ConfigShooterLow(&m_shooter, &m_feeder)); // RJ

  frc2::JoystickButton(&m_driver, (int)DriverButtons::A).WhileHeld(new VisionDrive(&m_vision, &m_driveTrain)); // A
  frc2::JoystickButton(&m_driver,(int)DriverButtons::B).WhileHeld(new LoaderOff(&m_loader)); // B
  frc2::JoystickButton(&m_driver,(int)DriverButtons::X).WhileHeld(new LoaderUp(&m_loader)); // X
  frc2::JoystickButton(&m_driver,(int)DriverButtons::Y).WhileHeld(new LoaderDown(&m_loader)); // Y

  frc2::JoystickButton(&m_operator, (int)OperatorButtons::LB).WhenPressed(&m_ReleaseInterlock);

  // LT and RT control intake on and reverse
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
     std::vector<frc::Trajectory::State> t_states = exampleTrajectory.States();

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
  // return m_chooser.GetSelected();

  double delay = m_delayChooser.GetSelected();


  switch(m_trajectoryChooser.GetSelected()) {
    case NoTrajectory:
      return nullptr;
    case ShootFromLine_L:
      return new frc2::SequentialCommandGroup {
        frc2::WaitCommand((units::second_t)delay),
        PullIntakeDown(&m_intake),
        AutoSetShootHigh(&m_shooter, &m_feeder),
        AimFireShooter(&m_shooter, &m_vision, &m_loader, &m_driveTrain, &m_feeder),
        // Call Backwards_Short trajectory
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_Backwards_Short_L, &AutoMove_Backwards_Short_R)   
      };
    case ShootFromLine_R:
      return new frc2::SequentialCommandGroup {
        frc2::WaitCommand((units::second_t)delay),
        PullIntakeDown(&m_intake),
        AutoSetShootHigh(&m_shooter, &m_feeder),
        frc2::PrintCommand("Shooting Start"),
        AimFireShooter(&m_shooter, &m_vision, &m_loader, &m_driveTrain, &m_feeder),
        frc2::PrintCommand("Shooting Complete"),
        // Call Backwards_Short trajectory
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_Backwards_Short_L, &AutoMove_Backwards_Short_R)   
      };

    case ShootFromLine_C:
      return new frc2::SequentialCommandGroup {
        frc2::WaitCommand((units::second_t)delay),
        PullIntakeDown(&m_intake),
        AutoSetShootHigh(&m_shooter, &m_feeder),
        AimFireShooter(&m_shooter, &m_vision, &m_loader, &m_driveTrain, &m_feeder),
        // Call Backwards_Short trajectory
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_Backwards_Short_L, &AutoMove_Backwards_Short_R)   
      };
    case ShootFromPwrPrt_L:
      return new frc2::SequentialCommandGroup {
        frc2::WaitCommand((units::second_t)delay),
        PullIntakeDown(&m_intake),
        AutoSetShootLow(&m_shooter, &m_feeder),
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_To_PwrPort_L_L, &AutoMove_To_PwrPort_L_R),  // then drive to trench: FIX THIS!
        FireShooter(&m_shooter, &m_loader, &m_feeder),
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_Backwards_Long_L, &AutoMove_Backwards_Long_R)   
      };
    case ShootFromPwrPrt_R:
      return new frc2::SequentialCommandGroup {
        frc2::WaitCommand((units::second_t)delay),
        PullIntakeDown(&m_intake),
        AutoSetShootLow(&m_shooter, &m_feeder),
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_To_PwrPort_R_L, &AutoMove_To_PwrPort_R_R),  // then drive to trench: FIX THIS!
        FireShooter(&m_shooter, &m_loader, &m_feeder),
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_Backwards_Long_L, &AutoMove_Backwards_Long_R)   
      };
    case ShootFromPwrPrt_C:
      return new frc2::SequentialCommandGroup {
        frc2::WaitCommand((units::second_t)delay),
        PullIntakeDown(&m_intake),
        AutoSetShootLow(&m_shooter, &m_feeder),
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_To_PwrPort_C_L, &AutoMove_To_PwrPort_C_R),  // then drive to trench: FIX THIS!
        FireShooter(&m_shooter, &m_loader, &m_feeder),
        AutonomousMotionProfile(&m_driveTrain, &AutoMove_Backwards_Long_L, &AutoMove_Backwards_Long_R)   
      };
    case GatherMoreBalls:
      return new frc2::SequentialCommandGroup {
        frc2::WaitCommand((units::second_t)delay),
        // Trajectory not yet complete
      };
  }

  return nullptr;
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