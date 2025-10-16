#ifndef DRIVETRAINSUBSYTEMS_H
#define DRIVETRAINSUBSYTEMS_H

#include "PIDController.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "lemlib/pose.hpp"

class DriveTrainSubsystem {
public:
  DriveTrainSubsystem();
  void drive(int throttle, int turn);
  void init();

  void auton();
  
  pros::MotorGroup leftMotorGroup;
  pros::MotorGroup rightMotorGroup; 
  pros::Imu imu1;
  pros::Imu imu2;
  lemlib::ExpoDriveCurve throttleCurve;
  lemlib::ExpoDriveCurve steerCurve;

  lemlib::ControllerSettings lateralController;
  lemlib::ControllerSettings angularController;

  pros::Rotation verticalRotationSensor;
  pros::Rotation horizontalRotationSensor;

  lemlib::TrackingWheel verticalTrackingWheel;
  lemlib::TrackingWheel horizontalTrackingWheel;

  lemlib::OdomSensors sensors;
  lemlib::Drivetrain drivetrain;
  lemlib::Chassis chassis;
};

#endif

