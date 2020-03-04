/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "DriveControllers/DriveController.h"

class CheesyDrive: public DriveController {
 public:
  CheesyDrive(SetWheelVelocityPercentage SetWheelVelocityPercentageFunction, int pidSlot_in);
  std::pair<double, double> GetLeftRightMotorOutputs(double throttle, double rotation) override;
 private:
  double kTurnSensitivity = 1.0;
  double mQuickStopAccumulator = 0;
};
