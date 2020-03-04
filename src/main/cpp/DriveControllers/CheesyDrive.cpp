/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveControllers/CheesyDrive.h"

CheesyDrive::CheesyDrive(SetWheelVelocityPercentage SetWheelVelocityPercentageFunction, int pidSlot_in) 
: DriveController(SetWheelVelocityPercentageFunction, pidSlot_in) {
}

std::pair<double, double> CheesyDrive::GetLeftRightMotorOutputs(double throttle, double rotation) {
    double overPower = 0.0;
    double angularPower = abs(throttle) * rotation * kTurnSensitivity - mQuickStopAccumulator;
    if (mQuickStopAccumulator > 1) {
        mQuickStopAccumulator -= 1;
    } else if (mQuickStopAccumulator < -1) {
        mQuickStopAccumulator += 1;
    } else {
        mQuickStopAccumulator = 0.0;
    }

    double rightPwm = throttle - angularPower;
    double leftPwm = throttle + angularPower;
    if (leftPwm > 1.0) {
        rightPwm -= overPower * (leftPwm - 1.0);
        leftPwm = 1.0;
    } else if (rightPwm > 1.0) {
        leftPwm -= overPower * (rightPwm - 1.0);
        rightPwm = 1.0;
    } else if (leftPwm < -1.0) {
        rightPwm += overPower * (-1.0 - leftPwm);
        leftPwm = -1.0;
    } else if (rightPwm < -1.0) {
        leftPwm += overPower * (-1.0 - rightPwm);
        rightPwm = -1.0;
    }
    return std::pair<double, double>(leftPwm, rightPwm);
}