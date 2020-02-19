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

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include <tuple>
#include "DataLogger.h"
#include "hwcfg.h"

#include "Subsystems/Vision.h"
#include "Subsystems/DriveTrain.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class VisionDrive: public frc2::CommandHelper<frc2::CommandBase, VisionDrive>  {
public:
	VisionDrive(Vision* vision, DriveTrain* drive);

	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End(bool interrupted) override;

private:
	Vision* m_vision;
	DriveTrain* m_drive;
};
