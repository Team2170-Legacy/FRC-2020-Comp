/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "JoystickAdapters/Exponential.h"

Exponential::Exponential(JoystickAdapter* controller, double exponent) {
    joystick = controller;
    m_exponent = exponent;
}

double Exponential::GetRawAxis(int i){
    double input = joystick->GetRawAxis(i);
   // return (exp2(fabs(input)*4)/16.0)* (input<0 ? -1:1);
   return pow(input, m_exponent);
}