/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "JoystickAdapters/Exponential.h"

Exponential::Exponential(JoystickAdapter* controller) {
    joystick = controller;
}

double Exponential::GetRawAxis(int i){
    return exp2(joystick->GetRawAxis(i)*4)/16.0;
}