#include "Subsystems/driveTrainSubsystem.hpp"
#include "constants.h"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "lemlib/pose.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include <iostream>
#include <sstream>

#include "Subsystems/clampSubsystem.hpp"
#include "Subsystems/driveTrainSubsystem.hpp"
#include "Subsystems/intakeSubsystem.hpp"
#include "Subsystems/ladyBrownSubsystem.hpp"

DriveTrainSubsystem::DriveTrainSubsystem()
    : leftMotorGroup(
          {PORT_VALUES::LEFT_1, PORT_VALUES::LEFT_2, PORT_VALUES::LEFT_3},
          pros::MotorGearset::blue),
      rightMotorGroup(
          {PORT_VALUES::RIGHT_1, PORT_VALUES::RIGHT_2, PORT_VALUES::RIGHT_3},
          pros::MotorGearset::blue),
      throttleCurve(
          OPERATOR_CONSTANTS::THROTTLE::DEADBAND, // joystick deadband out of
                                                  // 127
          OPERATOR_CONSTANTS::THROTTLE::MIN,  // minimum output where drivetrain
                                              // will move out of 127
          OPERATOR_CONSTANTS::THROTTLE::CURVE // expo curve gain
          ),
      steerCurve(
          OPERATOR_CONSTANTS::STEER::DEADBAND, // joystick deadband out of 127
          OPERATOR_CONSTANTS::STEER::MIN,  // minimum output where drivetrain
                                           // will move out of 127
          OPERATOR_CONSTANTS::STEER::CURVE // expo curve gain
          ),
      imu1(PORT_VALUES::IMU_1), imu2(PORT_VALUES::IMU_2),
      horizontalRotationSensor(PORT_VALUES::HORIZONTAL_ROTATION_SENSOR),
      horizontalTrackingWheel(&horizontalRotationSensor,
                              lemlib::Omniwheel::NEW_2,
                              CHASIS_VALUES::HORIZONTALTRACKING_WHEEL_OFFSET),
      verticalRotationSensor(PORT_VALUES::VERTICAL_ROTATION_SENSOR),
      verticalTrackingWheel(&verticalRotationSensor, lemlib::Omniwheel::NEW_2,
                            CHASIS_VALUES::LATERALTRACKING_WHEEL_OFFSET),
      lateralController(PID_CONSTANTS::LATERAL::KP,  // proportional gain (kP)
                        PID_CONSTANTS::LATERAL::KI,   // integral gain (kI)
                        PID_CONSTANTS::LATERAL::KD,   // derivative gain (kD)
                        0,   // anti windup
                        PID_CONSTANTS::LATERAL::SMALL_ERROR,   // small error range, in inches
                        PID_CONSTANTS::LATERAL::SMALL_TIMEOUT, // small error range timeout, in milliseconds
                        PID_CONSTANTS::LATERAL::LARGE_ERROR,   // large error range, in inches
                        PID_CONSTANTS::LATERAL::LARGE_TIMEOUT, // large error range timeout, in milliseconds
                        PID_CONSTANTS::LATERAL::SLEW    // maximum acceleration (slew)
                        ),
      angularController(PID_CONSTANTS::ANGULAR::KP, // proportional gain (kP)
                        PID_CONSTANTS::ANGULAR::KI,   // integral gain (kI)
                        PID_CONSTANTS::ANGULAR::KD,  // derivative gain (kD)
                        0,   // anti windup
                        PID_CONSTANTS::ANGULAR::SMALL_ERROR,   // small error range, in inches, 1
                        PID_CONSTANTS::ANGULAR::SMALL_TIMEOUT, // small error range timeout, in milliseconds, 100
                        PID_CONSTANTS::ANGULAR::LARGE_ERROR,   // large error range, in inches, 2
                        PID_CONSTANTS::ANGULAR::LARGE_TIMEOUT, // large error range timeout, in milliseconds, 500
                        PID_CONSTANTS::ANGULAR::SLEW    // maximum acceleration (slew)
                        ),
      sensors(&verticalTrackingWheel, // vertical tracking wheel
              nullptr, // vertical tracking wheel 2, set to nullptr as we don't
                       // have a second one
              &horizontalTrackingWheel, // horizontal tracking wheel
              nullptr, // horizontal tracking wheel 2, set to nullptr as we
                       // don't have a second one
              &imu1    // inertial sensor
              ),
      drivetrain(&leftMotorGroup,                // left motor group
                 &rightMotorGroup,               // right motor group
                 12.5,                           // 12.5 inch track width
                 lemlib::Omniwheel::NEW_325,     // using new 4" omnis
                 CHASIS_VALUES::RPM,             // drivetrain rpm is 360
                 CHASIS_VALUES::HORIZONTAL_DRIFT // horizontal drift is 8
                 ),
      chassis(drivetrain,        // drivetrain settings
              lateralController, // lateral PID settings
              angularController, // angular PID settings
              sensors,           // odometry sensors
              &throttleCurve, &steerCurve)
{

  // distanceDriven = 0;
  // x = 0;
  // y = 0;
}


void DriveTrainSubsystem::init() {
  // calibrate everything
  chassis.calibrate(); // calibrate sensors

  // set motors to brake
  leftMotorGroup.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
  rightMotorGroup.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);

  pros::Task screenTask([&]() {
    while (true) {
      lemlib::Pose pose = chassis.getPose();
      // print robot location to the brain screen
      pros::lcd::print(0, "X: %f", pose.x);         // x
      pros::lcd::print(1, "Y: %f", pose.y);         // y
      pros::lcd::print(2, "Theta: %f", pose.theta); // heading
      pros::lcd::print(3, "In Motion: %d",
                       chassis.isInMotion());                   // motion status
      pros::lcd::print(4, "IMU Theta: %f", imu1.get_heading()); // heading

      // log position telemetry
      lemlib::telemetrySink()->info("Chassis pose: x: %f, y: %f, theta: %f",
                                    pose.x, pose.y, pose.theta);

      // delay to save resources
      pros::delay(50);
    }
  });
}

void lemlib::Drivetrain::drive() {
  // Arcade Measurements
  int throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  // Makes the turning of the robot even more controlled when the thrust is 0,
  // as the robot's turning is proportional to the thrust of the robot has no
  // thrust. Based on an exponential drive curve.
  if (throttle <= 1) {
    turn = std::round(steerCurve.curve(turn));
  }

  chassis.arcade(throttle, -turn, false, OPERATOR_CONSTANTS::DESATURATE_BIAS);
}

void DriveTrainSubsystem::auton() {}