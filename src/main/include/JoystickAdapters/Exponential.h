/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "JoystickAdapters/JoystickAdapter.h"
#include <cmath>
class Exponential: public JoystickAdapter {
 private:
  JoystickAdapter* joystick;
  double m_exponent;
 public:
  Exponential(JoystickAdapter* controller, double exponent);
  double GetRawAxis(int i) override;
};
