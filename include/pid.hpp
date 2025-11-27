#pragma once

namespace PID_CONSTANTS {
namespace LATERAL {
constexpr double KP = 7;
constexpr double KI = 0;
constexpr double KD = 50;
} // namespace LATERAL

namespace ANGULAR {
constexpr double KP = 2.3;
constexpr double KI = 0;
constexpr double KD = 12;
} // namespace ANGULAR

namespace TEST_TYPE {
constexpr bool TEST_ANGULAR = true;
} // namespace TEST_TYPE
} // namespace PID_CONSTANTS