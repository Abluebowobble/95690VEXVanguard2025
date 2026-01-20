#pragma once
#include <functional>
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "globals.hpp"

namespace pros {

class ColorSensor : public pros::Optical {
public:
  ColorSensor(std::uint8_t port);

  globals::SensorColors get_color();
};
} // namespace pros