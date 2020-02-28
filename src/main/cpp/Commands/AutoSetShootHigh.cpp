/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutoSetShootHigh.h"
#include "Commands/SetHoodHigh.h"
#include "Commands/SetShooterSpeed.h"
#include <frc/smartdashboard/SmartDashboard.h>

AutoSetShootHigh::AutoSetShootHigh(Shooter* shooter, Feeder* feeder) :
  kHighShooterSpeed {frc::Preferences::GetInstance()->GetDouble("High Shooter Speed", 20.0)}
 {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands(
    SetHoodHigh(shooter),
    SetShooterSpeed(shooter, kHighShooterSpeed),
    frc2::InstantCommand([feeder] {feeder->RotateCCW();})
  );
}
