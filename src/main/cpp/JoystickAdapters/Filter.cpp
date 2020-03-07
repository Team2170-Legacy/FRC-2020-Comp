/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "JoystickAdapters/Filter.h"

Filter::Filter(JoystickAdapter* controller, char* str, double limit, units::time::second_t rate):
filter(frc::LinearFilter<double>::SinglePoleIIR(
      frc::Preferences::GetInstance()->GetDouble("Speed Time Constant", 0.01), 0.02_s)){
          joystick = controller;
}

double Filter::GetRawAxis(int i){
    filter.Calculate(joystick->GetRawAxis(i));
}