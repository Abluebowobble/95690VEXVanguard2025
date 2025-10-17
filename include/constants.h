#pragma once
#include "pros/misc.h"

namespace PORT_VALUES {
// drivetrain
constexpr int LEFT_1 = 14;
constexpr int LEFT_2 = 13;
constexpr int LEFT_3 = -12; // top motor
constexpr int RIGHT_1 = -19;
constexpr int RIGHT_2 = -20;
constexpr int RIGHT_3 = 18; // top motor

// magazine
constexpr int LOWER_MAGAZINE_MOTOR_PORT = 9;
constexpr int UPPER_MAGAZINE_MOTOR_PORT = 10;

// endeffector
constexpr int UPPER_ENDEFFECTOR_MOTOR_PORT = 2;
constexpr int LOWER_ENDEFFECTOR_MOTOR_PORT = 15;

// odometry
constexpr int HORIZONTAL_ROTATION_SENSOR = 1;
constexpr int VERTICAL_ROTATION_SENSOR = 3;
constexpr int IMU_1 = 17; // old
constexpr int IMU_2 = 11; // Second IMU port, new

// sensors
constexpr int L2_COLOR_SENSOR = 7;
constexpr int L3_COLOR_SENSOR = 8;

// pneumatics
constexpr char INTAKE_PNEUMATIC = 'A';
constexpr char WILL_PNEUMATIC = 'C';
constexpr char HOOD_PNEUMATIC = 'B';

} // namespace PORT_VALUES

namespace CHASIS_VALUES {
constexpr double TRACKWIDTH = 12.5;
constexpr double HORIZONTAL_DRIFT = 8;
constexpr int RPM = 450;
constexpr double LATERALTRACKING_WHEEL_OFFSET = 0;
constexpr double HORIZONTALTRACKING_WHEEL_OFFSET = -3.966;
} // namespace CHASIS_VALUES

namespace OPERATOR_CONSTANTS {
namespace THROTTLE {
constexpr int DEADBAND = 3;
constexpr int MIN = 10;
constexpr double CURVE = 1.03;
} // namespace THROTTLE

namespace STEER {
constexpr int DEADBAND = 3;
constexpr int MIN = 10;
constexpr double CURVE = 1.02;
} // namespace STEER

constexpr double DESATURATE_BIAS = 0.55;
} // namespace OPERATOR_CONSTANTS

namespace PID_CONSTANTS {
namespace LATERAL {
constexpr double KP = 0;
constexpr double KI = 0;
constexpr double KD = 0;
constexpr double SMALL_ERROR = 0;
constexpr int SMALL_TIMEOUT = 0;
constexpr double LARGE_ERROR = 0;
constexpr int LARGE_TIMEOUT = 0;
constexpr double SLEW = 0.0;
} // namespace LATERAL

namespace ANGULAR {
constexpr double KP = 1;
constexpr double KI = 0;
constexpr double KD = 50;
constexpr double SMALL_ERROR = 0;
constexpr int SMALL_TIMEOUT = 0;
constexpr double LARGE_ERROR = 0;
constexpr int LARGE_TIMEOUT = 0;
constexpr double SLEW = 0;
} // namespace ANGULAR
} // namespace PID_CONSTANTS

namespace VISION {
namespace RED {
constexpr double UPPER_BOUND = 20;
constexpr double LOWER_BOUND = 350;
} // namespace RED

namespace BLUE {
constexpr double UPPER_BOUND = 230; //around 224
constexpr double LOWER_BOUND = 210;

// 90-260
//
} // namespace BLUE
} // namespace VISION

namespace CONTROLLER_BUTTONS {
namespace MAGAZINE {
constexpr auto INTAKE = pros::E_CONTROLLER_DIGITAL_R1;
constexpr auto OUTTAKE = pros::E_CONTROLLER_DIGITAL_R2;
constexpr auto ANTI_JAM = pros::E_CONTROLLER_DIGITAL_X;

} // namespace MAGAZINE

namespace ENDEFFECTOR {
constexpr auto SCORE_HIGH = pros::E_CONTROLLER_DIGITAL_L1;
constexpr auto SCORE_MID = pros::E_CONTROLLER_DIGITAL_L2;
constexpr auto DISABLE_COLOR_SORTING = pros::E_CONTROLLER_DIGITAL_B;
} // namespace ENDEFFECTOR

namespace LIL_WILL {
constexpr auto TOGGLE = pros::E_CONTROLLER_DIGITAL_Y;
constexpr auto START = pros::E_CONTROLLER_DIGITAL_DOWN;
} // namespace LIL_WILL

namespace INTAKE {
constexpr auto TOGGLE = pros::E_CONTROLLER_DIGITAL_RIGHT;
} // namespace INTAKE
} // namespace CONTROLLER_BUTTONS

#pragma once
