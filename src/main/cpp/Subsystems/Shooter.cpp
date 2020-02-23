// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Shooter.h"
#include "frc/smartdashboard/SmartDashboard.h"

Shooter::Shooter() :
    kP(frc::Preferences::GetInstance()->GetDouble("Shoot kP", 0.0)),
    kFF(frc::Preferences::GetInstance()->GetDouble("Shoot kFF", 180.0e-6)),
    maxRPM(frc::Preferences::GetInstance()->GetDouble("Shoot RPM Max", 3000.0)),
    maxAccel(frc::Preferences::GetInstance()->GetDouble("Shoot Accel Max", 500.0)) {
    m_shooterEncoderLead.SetPositionConversionFactor(kGearRatio);

    m_shooterEncoderFollow.SetPositionConversionFactor(kGearRatio);
    m_shooterFollow.Follow(m_shooterLead, true);

    frc::SmartDashboard::PutNumber("Shooter RPM", m_shooterEncoderLead.GetVelocity());

    // Set min/max power
    m_pidShooterMotorLead.SetOutputRange(kMinOutput, kMaxOutput);
    m_pidShooterMotorLead.SetSmartMotionMaxVelocity(maxRPM);
    m_pidShooterMotorLead.SetSmartMotionMaxAccel(maxAccel);
    
    // Set kFF and kP ( after tuning, since gains have been already been determined )
    m_pidShooterMotorLead.SetP(kP);
    m_pidShooterMotorLead.SetFF(kFF);
}

void Shooter::Periodic() {
    if (ShooterEnabled == true) {
        printf("%f\n", CommandedVelocity);
        m_pidShooterMotorLead.SetReference(CommandedVelocity, rev::ControlType::kSmartVelocity);
    }
    else {
        m_pidShooterMotorLead.SetReference(0.0, rev::ControlType::kSmartVelocity);
    }
}

void Shooter::ShooterOff() {
    ShooterEnabled = false;
}

void Shooter::ShooterOn(double velocity) {
    printf("Shooter On\n");
    ShooterEnabled = true;
    CommandedVelocity = velocity;
}

void Shooter::SetHoodHigh() {
    m_solHood.Set(frc::DoubleSolenoid::kForward);
}

void Shooter::SetHoodLow() {
    m_solHood.Set(frc::DoubleSolenoid::kReverse);
}

bool Shooter::IsHoodHigh() {
    bool retVal = false;
    
    if (m_solHood.Get() == frc::DoubleSolenoid::kForward) {
        retVal = true;
    }

    return retVal;
}

bool Shooter::IsHoodLow() {
    bool retVal = false;
    
    if (m_solHood.Get() == frc::DoubleSolenoid::kReverse) {
        retVal = true;
    }

    return retVal;
}

 