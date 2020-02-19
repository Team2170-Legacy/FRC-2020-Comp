#pragma once

enum CANIDs {
	kLeftLeadID = 4,
	kLeftFollowID = 3,
	kRightLeadID = 1,
  kRightFollowID = 2,
	kShooterMotorID = 5,
	kIntakeMotorID = 6,
	kFeederMotorID = 7,
	kClimberMotorID = 8,
	kLoaderMotorID = 9,
	kFeederMotorID = 10
};

enum PCMIDs {
  kHoodSolFwd = 0,
  kHoodSolRev = 1,
	kIntakeSolFwd = 2,
	kIntakeSolRev = 3,
	kClimberSol = 4
};

enum PWMIDs {

};

enum DIOIDs {

};

enum HIDIDs {
	kDriver = 0,
	kOperator = 1
};