/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <tuple>
#include "Subsystems/DriveTrain.h"

class DriveController {
 public:
  typedef void SetWheelVelocityFunction(DriveTrain::*SetWheelVelocity)(double, double, int);
  //auto SetWheelVelocity = DriveTrain::SetWheelVelocity(double left, double right, int pidSlot);
  DriveController(SetWheelVelocity SetWheelVelocityFunction, int pidSlot_in);
  virtual std::pair<double, double> GetLeftRightMotorCommands(double throttle, double rotation);
  void SetMotorCommands(double throttle, double rotation);
 private:
  SetWheelVelocity SetWheelVelocityFunctionPtr;
  int pidSlot;
  

};
