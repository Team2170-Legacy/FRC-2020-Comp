#include "DataLogger.h"

DataLogger::DataLogger() {
	// TODO Auto-generated constructor stub
}

DataLogger::DataLogger(std::string name, std::string header) {
	mFilename = name;
	tLog.open(mFilename, std::ofstream::out | std::ofstream::trunc);
	tLog << "Time, " << header << std::endl;
}

std::string DataLogger::GetTimestamp() {
	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer[80];

  	time (&rawtime);
  	timeinfo = localtime(&rawtime);

  	strftime(buffer,sizeof(buffer),"%F_%H_%M",timeinfo);
  	std::string timeString(buffer);
	return timeString;
}

void DataLogger::Update() {
	if (tLog.is_open()) {
		tLog << LogTimer.Get() << "," 
				<< std::endl;
	}
}

void DataLogger::Flush() {
	tLog.flush();
}

void DataLogger::StartSession() {
	if (!tLog.is_open()) {
		tLog.open(mFilename, std::ofstream::out | std::ofstream::app);
	}
	LogTimer.Reset();
	LogTimer.Start();
}

void DataLogger::EndSession() {
	if (tLog.is_open()) {
		//Flush();
		tLog.close();
	}
	LogTimer.Stop();
}

DataLogger::~DataLogger() {
	// TODO Auto-generated destructor stub
	if (tLog.is_open()) {
		tLog.close();
	}
}

void DataLogger::VisionLogger(std::string name) {
    printf("construct\n");
	mFilename = name;
	tLog.open(mFilename, std::ofstream::out | std::ofstream::trunc);
	tLog << "Time,TargetLocked,VisionDriveActive,Distance,DistanceError,AngleError,AngleError_DB,Speed,Omega" << std::endl;
}

void DataLogger::WriteVisionData(bool targetLocked, bool visionDriveActive, double distance, double distanceError, double angleError, double angleError_DB, double speed, double omega) {
    tLog << std::to_string(LogTimer.Get()) + "," +  std::to_string(targetLocked) + "," + std::to_string(visionDriveActive) + "," + std::to_string(distance) + "," + std::to_string(distanceError) + "," + std::to_string(angleError) + "," + std::to_string(angleError_DB) + "," + std::to_string(speed) + "," + std::to_string(omega) << std::endl;
}

void DataLogger::DriveTrainLogger(std::string name) {
    printf("construct\n");
	mFilename = name;
	tLog.open(mFilename, std::ofstream::out | std::ofstream::trunc);
	tLog << "Time,LeftVelocityCommand,RightVelocityCommand,LeftActualVelocity,RightActualVelocity,LeftLeadVoltage,LeftFollowVoltage,RightLeadVoltage,RightFollowVoltage,LeftLeadCurrent,LeftFollowCurrent,RightLeadCurrent,RightFollowCurrent" << std::endl;
}

void DataLogger::WriteDriveTrainData(double leftVelocityCommand, double rightVelocityCommand, double leftActualVelocity, double rightActualVelocity, double leftLeadVoltage, double leftFollowVoltage, double rightLeadVoltage, double rightFollowVoltage, double leftLeadCurrent, double leftFollowCurrent, double rightLeadCurrent, double rightFollowCurrent)
{
	 tLog << std::to_string(LogTimer.Get()) + "," +  std::to_string(leftVelocityCommand) + "," + std::to_string(rightVelocityCommand) + "," + std::to_string(leftActualVelocity) + "," + std::to_string(rightActualVelocity) + "," + std::to_string(leftLeadVoltage) + "," + 
	 std::to_string(leftFollowVoltage) + "," + std::to_string(rightLeadVoltage) + "," + std::to_string(rightFollowVoltage) + "," 
	 + std::to_string(leftLeadCurrent) + "," + std::to_string(leftFollowCurrent) + "," + std::to_string(rightLeadCurrent) + "," + std::to_string(rightFollowCurrent) + "," << std::endl;
}

void DataLogger::LogData(std::string data) {
    tLog << std::to_string(LogTimer.Get()) + ", " +  data << std::endl;
}