/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "frc2/command/button/JoystickButton.h"
#include "frc/smartdashboard/SmartDashboard.h"

RobotContainer::RobotContainer() {
  m_driveTrain.SetDefaultCommand(TeleopDrive(&m_driveTrain));

  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {}