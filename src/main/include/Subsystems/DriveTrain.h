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

#include "frc/commands/Subsystem.h"
#include "frc/Preferences.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "frc/Compressor.h"
#include "frc/PowerDistributionPanel.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "rev/CANSparkMax.h"
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/geometry/Pose2d.h>
#include <frc/ADXRS450_Gyro.h>
#include <frc/geometry/Rotation2d.h>


/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrain: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
std::shared_ptr<frc::Compressor> compressor;
std::shared_ptr<frc::PowerDistributionPanel> powerDistributionPanel;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS


	// CAN Spark IDs
	enum SparkCANID {
		kLeftLeadID = 4,
		kLeftFollowID = 3,
		kRightLeadID = 1,
		kRightFollowID = 2
	};
	rev::CANSparkMax m_leftLead{kLeftLeadID, rev::CANSparkMax::MotorType::kBrushless};
	rev::CANSparkMax m_leftFollow{kLeftFollowID, rev::CANSparkMax::MotorType::kBrushless};
	rev::CANSparkMax m_rightLead{kRightLeadID, rev::CANSparkMax::MotorType::kBrushless};
	rev::CANSparkMax m_rightFollow{kRightFollowID, rev::CANSparkMax::MotorType::kBrushless};
	rev::CANEncoder m_leftEncoder{m_leftLead.GetEncoder()};
	rev::CANEncoder m_rightEncoder{m_rightLead.GetEncoder()};
	rev::CANPIDController m_pidControllerL{m_leftLead.GetPIDController()};
	rev::CANPIDController m_pidControllerR{m_rightLead.GetPIDController()};

	const double kGearRatio = 5.95;
	const double kWheelDiameter;
	//const double ft = 0.305;
	const double d = (25.75/12); 

	// PID Gains for closed-loop velocity control
	const double kP, kI = 0, kD = 0, kIz = 0, kFF, kMaxOutput = 1, kMinOutput = -1;	

	// Max RPM for motors
	const double maxRPM = 5600;
	const double maxFeetPerSec;
	const double maxAccelPerSec;
	const bool kGyroReverse = false;



	frc::DifferentialDrive m_Drive{m_leftLead, m_rightLead};
	frc::DifferentialDriveOdometry m_odometry{frc::Rotation2d(units::degree_t(GetHeading()))};
	frc::ADXRS450_Gyro m_gyro;
public:
DriveTrain();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void VelocityArcadeDrive(double xSpeed, double zRotation, bool squaredInputs);
	void ResetEncoders();
	double GetAverageEncoderDistance();
	void SetMaxOutput(double maxOutput);
	double GetHeading();
	double GetTurnRate();
	frc::Pose2d GetPose();
	frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();
	void ResetOdometry(frc::Pose2d pose);


};
