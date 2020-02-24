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
#include "rev/CANSparkMax.h"
#include "frc/Preferences.h"
#include "frc/DoubleSolenoid.h"
#include "hwcfg.h"
#include "DataLogger.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

#define DEFAULT_SHOOTER_VELOCITY 3000.0

/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter: public frc2::SubsystemBase {
private:
	const double kGearRatio = 1.0;
	rev::CANSparkMax m_shooterLead{CANIDs::kShooterMotorID, rev::CANSparkMax::MotorType::kBrushless};
	rev::CANEncoder m_shooterEncoderLead{m_shooterLead.GetEncoder()};
	rev::CANPIDController m_pidShooterMotorLead{m_shooterLead.GetPIDController()};

	rev::CANSparkMax m_shooterFollow{CANIDs::kShooterMotorID2, rev::CANSparkMax::MotorType::kBrushless};

	// PID Gains for closed-loop velocity control
	const double kP, kI = 0, kD = 0, kIz = 0, kFF, kMaxOutput = 1, kMinOutput = -1;	

	// Max RPM for motors
	const double maxRPM;
	const double maxAccel;
	double CommandedVelocity = 0.0;
	bool ShooterEnabled = false;
	//double solenoid for the hood
	frc::DoubleSolenoid m_solHood{PCMIDs::kHoodSolFwd, PCMIDs::kHoodSolRev};

	// Logger object
	DataLogger shooterLogger;
public:
Shooter();
	void Periodic() override;
	void ShooterOff(void);
	void ShooterOn(double velocity = DEFAULT_SHOOTER_VELOCITY);
	bool IsShooterOn() {return ShooterEnabled;}
	double GetShooterSpeed() {return CommandedVelocity;}
	double GetMotorVelocity() {return m_shooterEncoderLead.GetVelocity();}

	void SetHoodHigh();
	void SetHoodLow();

	bool IsHoodHigh();
	bool IsHoodLow();

	// Logging methods
	void EnableLogging();
	void DisableLogging();

};
