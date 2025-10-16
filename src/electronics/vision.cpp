#include "electronics/vision.hpp"
#include "constants.hpp"
#include "globals.hpp"

using namespace pros;
using namespace globals;

ColorSensor::ColorSensor(std::uint8_t port) : pros::Optical(port) {}

SensorColors ColorSensor::get_color() {
  int hue = this->get_hue();
  // return the colours if the vision sensor actually sees balls
  if (hue > VISION::BLUE::LOWER_BOUND && hue < VISION::BLUE::UPPER_BOUND) {
    return SensorColors::BLUE;
  } else if (hue > VISION::RED::LOWER_BOUND || hue < VISION::RED::UPPER_BOUND) {
    return SensorColors::RED;
  }

  // return the colour that is not of our alliance
  return SensorColors::NONE;
}
