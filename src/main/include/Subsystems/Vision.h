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
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/EntryListenerFlags.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "frc/Preferences.h"

#include "DataLogger.h"
#include "hwcfg.h"


#include <math.h>
#include <cmath>
#include <tuple>

#define Deg2Rad 3.14159/180
#define inches 1.0/12

/**
 *
 *
 * @author ExampleAuthor
 */
class Vision: public frc2::SubsystemBase {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	
	// network table entries for limelight communication 
	nt::NetworkTableEntry tx;
	nt::NetworkTableEntry ty;
	nt::NetworkTableEntry tv;
	nt::NetworkTableEntry tl;
	nt::NetworkTableEntry getPipe;
	nt::NetworkTableEntry ledMode;
	nt::NetworkTableEntry camMode;
	nt::NetworkTableEntry setPipe;
	nt::NetworkTableEntry snapshot;

	// network table entries for vision drive
	nt::NetworkTableEntry nt_visionDrive;
	nt::NetworkTableEntry nt_distance;
	nt::NetworkTableEntry nt_kP_Omega;
	nt::NetworkTableEntry nt_kI_Omega;
	nt::NetworkTableEntry nt_angle_DB;
	nt::NetworkTableEntry nt_kP_Distance;
	
	// for distance calculation
	const double powerportVisionTargetHeight = (6 + 9.25 * inches) + (1 + 5.0 * inches)/2; // height of the center of the vision target (ft)
	const double cameraHeight = 44.0 * inches; // height that the camera is mounted at (ft)
	const double cameraAngle = 35; // angle camera is mounted at from horizontal (degrees)
	const double cameraDistanceFromFrontBumper = 30.0 * inches; // (ft)
	double optimalShootingDistance = 10; // optimal distance from powerport to shoot from (ft)

	// For VisionDrive PID controller
	double angleErrorDeadband = 0.5; // degrees
	double kP_Omega = -0.12; 
	double kI_Omega = -0.3; 
	double kP_Distance = -0;
	double distanceErrorDeadband = 0; // feet 
	double omegaLimiter = 0.46;
	double omegaIntegrator = 0;
	double speedLimiter = 0.7;
	const double deltaTime = 0.02;

	// for data logging
	DataLogger visionLogger;
	bool visionDriveActive = false;
	double distance = 0;	
	double distanceError = 0;
	double distanceError_DB = 0;
	double angleError = 0;
	double angleError_DB = 0;
	double speed = 0;
	double omega = 0;

	// for taking snapshots during visiondrives
	bool takePeriodicSnapshots = true;
	nt::NetworkTableEntry nt_takePeriodicSnapshots;
	int loopsBetweenImages = 10;
	int loopsSinceLastImage = 0;

	// makes sure the LED and vision processing is on only when vision drive is being used
	// should be set to true during competitions, false when calibrating
	bool competitionMode = true;
	nt::NetworkTableEntry nt_competitionMode;

public:
  Vision();
    enum Pipeline {powerport = 0};
	enum LEDMode {currentPipelineMode = 0, forceOff = 1, forceBlink = 2, forceOn = 3};

	void Periodic() override;

	bool TargetIsLocked();
	double GetXAngleToTarget();
	double GetDistanceToPowerport();
	double GetLatency();
	void SetLEDMode(LEDMode ledModeToSet);
	void SetCamMode(bool visionProcessingEnabled);
	void ToggleCamMode();
	void SetPipeline(Pipeline pipeline);
	void TakeSnapshot();
	void VisionSteerInit();
	std::pair<double, double> SteerToLockedTarget(void);
	void VisionSteerEnd();
	void EnableLogging();
	void DisableLogging();
};
