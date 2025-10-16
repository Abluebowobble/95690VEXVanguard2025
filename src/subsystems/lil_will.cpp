#include "subsystems/lil_will.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/misc.h"

using namespace globals;

LilWill::LilWill()
    : will_pneumatic(PORT_VALUES::WILL_PNEUMATIC, false, false),
      hood_pneumatic(PORT_VALUES::HOOD_PNEUMATIC, false, false),
      is_set_for_start(false) {}

void LilWill::toggle() {
  if (!is_set_for_start) {
    set_start();
    return;
  }
  will_pneumatic.toggle();
  hood_pneumatic.toggle();
}

void LilWill::set_start() {
  will_pneumatic.set_value(false);
  hood_pneumatic.set_value(true);
  is_set_for_start = true;
}

void LilWill::run() {
  if (controller.get_digital_new_press(CONTROLLER_BUTTONS::LIL_WILL::TOGGLE)) {
    toggle();
  }
}
