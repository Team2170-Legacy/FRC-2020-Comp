/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "JoystickAdapters/JoystickAdapter.h"
#include "JoystickAdapters/JoystickConstants.h"

class Deadband: public JoystickAdapter{
 private:
  JoystickAdapter* joystick;
 double limit;

 public:
  Deadband(JoystickAdapter* controller, double lim);
  double GetRawAxis(int axis);
};
