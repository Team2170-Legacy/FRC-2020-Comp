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
	dataOutPin1.reset(new frc::DigitalOutput(1));
	dataOutPin2.reset(new frc::DigitalOutput(2));
	dataOutPin3.reset(new frc::DigitalOutput(3));
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
	frc::SmartDashboard::PutNumber("LED Code",0);
}

void Robot::SetupAutoOptions() {
	oi.reset(new OI());

/*
	double StartDelay = frc::Preferences::GetInstance()->GetDouble("Auto Start Delay", 3.0);

	// Add commands to Autonomous Sendable Chooser
	chooser.AddDefault("A Do Nothing", nullptr);
	chooser.AddObject("B Drive Straight",
			new AutonomousMotionProfile(&AutoMove_Straight_L, &AutoMove_Straight_R));
	*/
	
}

void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	m_container.EndDataLogging();
}

void Robot::DisabledPeriodic() {
	sendLEDCode(LEDCodes::Off);
}

void Robot::AutonomousInit() {
	m_autonomousCommand = m_container.GetAutonomousCommand();

	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Schedule();
	}
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
	m_container.StartDataLogging();
}

void Robot::TeleopPeriodic() {
	int code = frc::SmartDashboard::GetNumber("LED Code",0);
	sendLEDCode(code);
}

void Robot::sendLEDCode(int code) {
	// Convert integer code to 3 binary bits to send on DIOs
	// Last digit (index 2) is 2^0 spot
	int dataOut[3];
    dataOut[2] = code % 2;
    dataOut[1] = (code / 2) % 2;
    dataOut[0] = (code / 4) % 2;

    dataOutPin1->Set(dataOut[0]);   // Yellow wire
    dataOutPin2->Set(dataOut[1]);   // Orange wire
    dataOutPin3->Set(dataOut[2]);   // Black wire
}

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif
