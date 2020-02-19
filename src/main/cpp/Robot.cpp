// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

#include <hal/FRCUsageReporting.h>

#include <frc2/command/CommandScheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their Requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	m_container.EndDataLogging();
}

void Robot::DisabledPeriodic() {
	frc2::CommandScheduler::GetInstance().Run();
}

void Robot::AutonomousInit() {
#if 0

	autonomousCommand = chooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
#endif
}

void Robot::AutonomousPeriodic() {
	frc2::CommandScheduler::GetInstance().Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();

	m_container.StartDataLogging();
}

void Robot::TeleopPeriodic() {
	frc2::CommandScheduler::GetInstance().Run();
}

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif
