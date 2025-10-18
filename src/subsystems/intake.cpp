#include "subsystems/Intake.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏

using namespace globals;

Intake::Intake()
    : motor(PORT_VALUES::INTAKE_MOTOR_PORT),
      intake_pneumatic(PORT_VALUES::INTAKE_PNEUMATIC, true, false) {
  // pros::Task check_voltage_task([this]() {
  //   lower_motor.get_voltage();
  //   upper_motor.get_voltage();
  // });
}

void Intake::init() { motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); }

void Intake::toggle() { intake_pneumatic.toggle(); }

void Intake::set_volts(int voltage) { motor.move(voltage); }

void Intake::intake() { set_volts(127); }

void Intake::outtake() { set_volts(-127); }

void Intake::stop() { motor.move(0); }

void Intake::run() {

  // outtake
  if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::OUTTAKE)) {
    outtake();
  }
  // intake
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

  if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::TOGGLE))
    intake_pneumatic.retract();
  else
    intake_pneumatic.extend();
}