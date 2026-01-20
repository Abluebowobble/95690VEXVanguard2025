#include "subsystems/hood.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/misc.h"

using namespace globals;

Hood::Hood() : hood_pneumatic(PORT_VALUES::HOOD_PNEUMATIC, true, true) {}

void Hood::toggle() { hood_pneumatic.toggle(); }

void Hood::down() { hood_pneumatic.extend(); }

void Hood::up() { hood_pneumatic.retract(); }

void Hood::run() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
    hood_pneumatic.toggle();
  }
}