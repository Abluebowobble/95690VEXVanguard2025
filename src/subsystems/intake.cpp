#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "subsystems/Intake.hpp"

using namespace globals;

Intake::Intake()
    : lower_motor(PORT_VALUES::LOWER_INTAKE_MOTOR_PORT),
      upper_motor(PORT_VALUES::UPPER_INTAKE_MOTOR_PORT),
      intake_pneumatic(PORT_VALUES::INTAKE_PNEUMATIC, false, true) {
  // pros::Task check_voltage_task([this]() {
  //   lower_motor.get_voltage();
  //   upper_motor.get_voltage();
  // });
}

void Intake::init() {
  lower_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  upper_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Intake::toggle() { intake_pneumatic.toggle(); }

void Intake::set_volts(int voltage) {
  upper_motor.move(voltage);
  lower_motor.move(voltage);
}

void Intake::intake() { set_volts(127); }

void Intake::outtake() { set_volts(-127); }

void Intake::stop() {
  lower_motor.move(0);
  upper_motor.move(0);
}

void Intake::run() {

  // outtake
  if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::OUTTAKE)) {
    outtake();
  }
  // intake
  else if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::INTAKE)|| controller.get_digital(
               CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_HIGH) ||
           controller.get_digital(CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_MID)) {
    intake();
  } else if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::INTAKE) && controller.get_digital(CONTROLLER_BUTTONS::INTAKE::OUTTAKE)) {
    intake();
  } 
  else
    stop();

  if (controller.get_digital_new_press(CONTROLLER_BUTTONS::INTAKE::TOGGLE))
    toggle();

    // || controller.get_digital(
          //      CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_HIGH) ||
          //  controller.get_digital(CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_MID)
}