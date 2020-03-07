/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "JoystickAdapters/JoystickAdapter.h"

JoystickAdapter::JoystickAdapter(std::shared_ptr<frc::XboxController> stick) {
    joystick = stick;
}
double JoystickAdapter::GetRawAxis(int i){
    joystick->GetRawAxis(i);
}