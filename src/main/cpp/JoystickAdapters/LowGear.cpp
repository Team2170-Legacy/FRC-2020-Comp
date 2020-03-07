/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "JoystickAdapters/LowGear.h"

LowGear::LowGear(JoystickAdapter* controller, double r) {
    joystick = controller;
    ratio = r;
}

double LowGear::GetRawAxis(int i){
    return joystick->GetRawAxis(i)*ratio;
}