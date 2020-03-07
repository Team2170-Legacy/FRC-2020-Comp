/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "JoystickAdapters/JoystickAdapter.h"
#include <cmath>


class RateLimiter : public JoystickAdapter {
 private:
  JoystickAdapter* joystick;
  double delta;
  double tn_1;

 public:
  RateLimiter(JoystickAdapter* controller, double d);
  double GetRawAxis(int i);
};