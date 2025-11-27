#include "subsystems/intake.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/misc.h"

using namespace globals;

Intake::Intake()
    : lower_motor(PORT_VALUES::LOWER_INTAKE_MOTOR_PORT),
      upper_motor(PORT_VALUES::UPPER_INTAKE_MOTOR_PORT),
      basket_pneumatic(PORT_VALUES::BASKET_PNEUMATIC, true) {}

void Intake::init() {
  upper_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  lower_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Intake::toggle() { basket_pneumatic.toggle(); }

void Intake::set_volts(int voltage) {
  upper_motor.move(voltage);
  lower_motor.move(voltage);
}

void Intake::intake() { set_volts(127); }

void Intake::outtake() { set_volts(-127); }

void Intake::stop() { set_volts(0); }

void Intake::run() {

  // outtake
  if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::OUTTAKE)) {
    outtake();
  } // intake
  else if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::INTAKE) ||
           controller.get_digital(
               CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_HIGH) ||
           controller.get_digital(CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_MID)) {
    intake();
  } else if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::INTAKE) &&
             controller.get_digital(CONTROLLER_BUTTONS::INTAKE::OUTTAKE)) {
    intake();
  } else
    stop();

  if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::INTAKE) &&
             controller.get_digital(CONTROLLER_BUTTONS::INTAKE::OUTTAKE))
    basket_pneumatic.extend();
  else
    basket_pneumatic.retract();
}