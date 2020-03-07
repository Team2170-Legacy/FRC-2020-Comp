/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "JoystickAdapters/RateLimiter.h"

RateLimiter::RateLimiter(JoystickAdapter* controller, double d) {
    joystick = controller;
    delta = d;
}

double RateLimiter::GetRawAxis(int i){
    double tn = joystick->GetRawAxis(i);
    double diff = fabs(tn_1 - tn);
    tn_1 = tn;
    return (diff < delta ? diff:delta);
}