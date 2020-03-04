/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveControllers/ArcadeVelocityDrive.h"

ArcadeVelocityDrive::ArcadeVelocityDrive(SetWheelVelocityPercentage SetWheelVelocityPercentageFunction, int pidSlot_in) 
: DriveController(SetWheelVelocityPercentageFunction, pidSlot_in) {
}

std::pair<double, double> ArcadeVelocityDrive::GetLeftRightMotorOutputs(double throttle, double rotation) {

    double moveValue = throttle;
    double rotateValue = rotation;

    // local variables to hold the computed PWM values for the motors
    double leftMotorOutput = 0;
    double rightMotorOutput = 0;

    // LeftMove and leftRotate limits to +-1.0
    if (moveValue > 1.0)
    {
        moveValue = 1.0;
    }
    if (moveValue < -1.0)
    {
        moveValue = -1.0;
    }
    if (rotateValue > 1.0)
    {
        rotateValue = 1.0;
    }
    if (rotateValue < -1.0)
    {
        rotateValue = -1.0;
    }

    if (moveValue > 0.0)
    {
        if (rotateValue > 0.0)
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = std::max(moveValue, rotateValue);
        }
        else
        {
            leftMotorOutput = std::max(moveValue, -rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
    }
    else
    {
        if (rotateValue > 0.0)
        {
            leftMotorOutput = -std::max(-moveValue, rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
        else
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = -std::max(-moveValue, -rotateValue);
        }
    }
    return std::pair<double, double>(leftMotorOutput, rightMotorOutput);
}