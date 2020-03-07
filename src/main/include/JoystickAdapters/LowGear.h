/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "JoystickAdapters/JoystickAdapter.h"

class LowGear: public JoystickAdapter {
 private:
  JoystickAdapter* joystick;
  double ratio;

 public:
  LowGear(JoystickAdapter* controller, double r);
  double GetRawAxis(int i);

};
