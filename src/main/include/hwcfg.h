#pragma once

enum CANIDs {
	kLeftLeadID = 4,
	kLeftFollowID = 3,
	kRightLeadID = 1,
    kRightFollowID = 2,
	kShooterMotorID = 5,
	kIntakeMotorID = 6,
	kLoaderMotorID = 7,
	kFeederMotorID = 8
};

enum PCMIDs {
  kHoodSolFwd = 0,
  kHoodSolRev = 1,
	kIntakeSolFwd = 2,
	kIntakeSolRev = 3
};

enum PWMIDs {

};

enum DIOIDs {

};

enum HIDIDs {
	kDriver = 0,
	kOperator = 1
};