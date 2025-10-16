#include "subsystems/intake.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏

using namespace globals;

Intake::Intake() : intake_pneumatic(PORT_VALUES::INTAKE_PNEUMATIC, false, true) {}

void Intake::toggle() { intake_pneumatic.toggle(); }


void Intake::run() {
  if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::TOGGLE))
    toggle();
}