#include "subsystems/lil_will.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/misc.h"

using namespace globals;

LilWill::LilWill() : will_pneumatic(PORT_VALUES::WILL_PNEUMATIC, false, false) {}

void LilWill::toggle() { will_pneumatic.toggle(); }

void LilWill::down() { will_pneumatic.extend(); }

void LilWill::up() { will_pneumatic.retract(); }

void LilWill::run() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
    will_pneumatic.toggle();
  }
}
