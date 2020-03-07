/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "JoystickAdapters/Deadband.h"

Deadband::Deadband(JoystickAdapter* controller, double lim) {
    joystick = controller;
    limit = deadband_limit;
}

double Deadband::GetRawAxis(int i){
    double axisInput = joystick->GetRawAxis(i);
    return fabs(axisInput) > limit ? axisInput : 0.0;
}