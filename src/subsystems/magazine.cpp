#include "subsystems/magazine.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏

using namespace globals;

Magazine::Magazine()
    : lower_motor(PORT_VALUES::LOWER_MAGAZINE_MOTOR_PORT),
      upper_motor(PORT_VALUES::UPPER_MAGAZINE_MOTOR_PORT) {
        // pros::Task check_voltage_task([this]() {
        //   lower_motor.get_voltage();
        //   upper_motor.get_voltage();
        // });
      }

void Magazine::init() {
  lower_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  upper_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Magazine::set_volts(int voltage) {
  upper_motor.move(voltage);
  lower_motor.move(voltage);
}

void Magazine::intake() { set_volts(127); }

void Magazine::outtake() { set_volts(-127); }

void Magazine::stop() {
  lower_motor.move(0);
  upper_motor.move(0);
}

void Magazine::run() {

  // outtake
  if (controller.get_digital(CONTROLLER_BUTTONS::MAGAZINE::OUTTAKE)) {
    outtake();
  }
  // intake
  else if (controller.get_digital(CONTROLLER_BUTTONS::MAGAZINE::INTAKE)) {
    intake();
  } else
    stop();
}