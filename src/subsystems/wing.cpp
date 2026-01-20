#include "subsystems/lil_will.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/misc.h"
#include "subsystems/wing.hpp"

using namespace globals;

Wing::Wing()
    : wing_pneumatic(PORT_VALUES::WING_PNEUAMTIC, false, true)
      {}

void Wing::toggle() {
  wing_pneumatic.toggle();
}

void Wing::run() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    toggle();
  }
}