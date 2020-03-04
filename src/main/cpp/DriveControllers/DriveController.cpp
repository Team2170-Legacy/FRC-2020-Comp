/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveControllers/DriveController.h"

DriveController::DriveController(SetWheelVelocityPercentage SetWheelVelocityPercentageFunction, int pidSlot_in) {
    SetWheelVelocityFunctionPercentagePtr = SetWheelVelocityPercentageFunction;
    pidSlot = pidSlot_in;
}

void DriveController::SetMotorCommands(double throttle, double rotation) {
    std::pair<double, double> commands = GetLeftRightMotorOutputs(throttle, rotation);
    (SetWheelVelocityFunctionPercentagePtr)(commands.first, commands.second, pidSlot);
}

