/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "JoystickAdapters/JoystickAdapter.h"
#include "frc/LinearFilter.h"
#include "units/units.h"
#include "frc/Preferences.h"

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class Filter: public JoystickAdapter {
 private:
  frc::LinearFilter<double> filter;
  JoystickAdapter* joystick;

 public:
  Filter(JoystickAdapter* controller, char* str, double limit, units::time::second_t rate);
  double GetRawAxis(int axis);
};
