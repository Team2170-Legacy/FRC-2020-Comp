// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once

#include "frc2/command/SubsystemBase.h"
#include "ctre/Phoenix.h"
#include "hwcfg.h"

#define DEFAULT_LOADER_VOLTS 1.0
/**
 *
 *
 * @author ExampleAuthor
 */
class Loader: public frc2::SubsystemBase {
private:
	WPI_VictorSPX m_loaderMotor{CANIDs::kLoaderMotorID};
public:
	Loader();
	void Periodic() override;
	void LoaderUp(double speed = DEFAULT_LOADER_VOLTS){m_loaderMotor.Set(speed);}
	void LoaderDown(double speed = DEFAULT_LOADER_VOLTS){m_loaderMotor.Set(-speed);}
	void LoaderStop(void){m_loaderMotor.Set(0.0);}

};

