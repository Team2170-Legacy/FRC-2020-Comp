/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>
#include "frc/XboxController.h"
#include "JoystickAdapters/JoystickAdapter.h"

class RawInput:JoystickAdapter {
  private:
    std::shared_ptr<frc::XboxController> joystick;

 public:
  RawInput(std::shared_ptr<frc::XboxController> driver);
  double GetRawAxis(int i){joystick->GetRawAxis(i);}
};
