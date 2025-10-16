#pragma once

namespace PORT_VALUES {
// drivetrain
constexpr int LEFT_1 = 20;
constexpr int LEFT_2 = 19;
constexpr int LEFT_3 = -18;
constexpr int RIGHT_1 = -12;
constexpr int RIGHT_2 = -13;
constexpr int RIGHT_3 = 14;

// endeffector
constexpr int UPPER_ENDEFFECTOR_MOTOR_PORT = 4;
constexpr int LOWER_ENDEFFECTOR_MOTOR_PORT = 3;

// magazine
constexpr int LOWER_MAGAZINE_MOTOR_PORT = 1;
constexpr int UPPER_MAGAZINE_MOTOR_PORT = 2;

// odometry
constexpr int HORIZONTAL_ROTATION_SENSOR = 6;
constexpr int VERTICAL_ROTATION_SENSOR = 5;
constexpr int IMU = 16;

// pneumatics
constexpr int LIL_WILL = 'A';
 
// sensors
constexpr int L2_COLOR_SENSOR = 8;
constexpr int L3_COLOR_SENSOR = 7;
} // namespace PORT_VALUES

namespace CHASIS_VALUES {
constexpr double TRACKWIDTH = 12;
constexpr double HORIZONTAL_DRIFT = 8;
constexpr int RPM = 450;
constexpr double LATERALTRACKING_WHEEL_OFFSET = 0;
constexpr double HORIZONTALTRACKING_WHEEL_OFFSET = -3.966;
// constexpr double
} // namespace CHASIS_VALUES

namespace OPERATOR_CONSTANTS {
namespace THROTTLE {
constexpr int DEADBAND = 3;
constexpr int MIN = 10;
constexpr double CURVE = 1.019; //1.019
} // namespace THROTTLE

namespace STEER {
constexpr int DEADBAND = 3;
constexpr int MIN = 10;
constexpr double CURVE = 1.02; //1.02
} // namespace STEER

constexpr double DESATURATE_BIAS = 0.75;
} // namespace OPERATOR_CONSTANTS

namespace PID_CONSTANTS {
namespace LATERAL {
constexpr double KP = 0.5;
constexpr double KI = 0;
constexpr double KD = 3;
constexpr double SMALL_ERROR = 2.0; // Stop when within 2 inches
constexpr int SMALL_TIMEOUT = 200; // Wait 200ms in tolerance
constexpr double LARGE_ERROR = 4.0; // Large error zone
constexpr int LARGE_TIMEOUT = 1000; // Long timeout
constexpr double SLEW = 0.0;
} // namespace LATERAL

namespace ANGULAR {
constexpr double KP = 40;  // Just above deadband threshold
constexpr double KI = 0;
constexpr double KD = 3;  // Reduce damping to allow small corrections
constexpr double SMALL_ERROR = 0; // Stop when within 3 degrees
constexpr int SMALL_TIMEOUT = 00; // Wait 200ms in tolerance
constexpr double LARGE_ERROR = 0; // Large error zone
constexpr int LARGE_TIMEOUT = 0; // Long timeout
constexpr double SLEW = 0;
} // namespace ANGULAR
} // namespace PID_CONSTANTS

namespace VISION {
namespace RED {
constexpr double UPPER_BOUND = 10;
constexpr double LOWER_BOUND = 340;
} // namespace RED

namespace BLUE {
constexpr double UPPER_BOUND = 260;
constexpr double LOWER_BOUND = 90;
} // namespace BLUE
} // namespace VISION

#pragma once