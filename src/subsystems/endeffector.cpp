#include "subsystems/endeffector.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/misc.h"

using namespace globals;

EndEffector::EndEffector()
    : upper_motor(PORT_VALUES::UPPER_ENDEFFECTOR_MOTOR_PORT),
      lower_motor(PORT_VALUES::LOWER_ENDEFFECTOR_MOTOR_PORT),
      L2_color_sensor(PORT_VALUES::L2_COLOR_SENSOR),
      L3_color_sensor(PORT_VALUES::L3_COLOR_SENSOR), eject_bottom(false),
      eject_top(false), manual_control(false), stop_for_indexing(false) {
  pros::Task(
      [](void *param) {
        static_cast<EndEffector *>(param)->set_L2_color(param);
      },
      this, "L2 Color Task");

  pros::Task(
      [](void *param) {
        static_cast<EndEffector *>(param)->set_L3_color(param);
      },
      this, "L3 Color Task");
}

void EndEffector::set_L2_color(void *param) {
  pros::delay(10);
  while (true) {
    L2_color = L2_color_sensor.get_color();
    pros::delay(100);
  }
}

void EndEffector::set_L3_color(void *param) {
  pros::delay(10);
  while (true) {
    L3_color = L3_color_sensor.get_color();
    pros::delay(20);
  }
}

bool EndEffector::should_eject_L2() {
  return L2_color != globals::SensorColors::NONE &&
         L2_color != globals::alliance;
}

bool EndEffector::should_eject_L3() {
  return L3_color != globals::SensorColors::NONE &&
         L3_color != globals::alliance;
}

globals::SensorColors EndEffector::get_L2_color() { return L2_color; }

globals::SensorColors EndEffector::get_L3_color() { return L3_color; }

double EndEffector::get_L2_hue() { return L2_color_sensor.get_hue(); }

double EndEffector::get_L3_hue() { return L3_color_sensor.get_hue(); }

void EndEffector::index() {
  if (L3_color_sensor.get_proximity() > 200) {
    stop_for_indexing = true;
  }

  if (stop_for_indexing) {
    stop();
  } else {
    basket_intake();
  }
}

void EndEffector::init() {
  L2_color_sensor.set_led_pwm(100);
  L3_color_sensor.set_led_pwm(100);

  upper_motor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  lower_motor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void EndEffector::score_L3() {
  lower_motor.move(127);
  upper_motor.move(-127);
}

void EndEffector::score_L2() { set_volts(-127); }

void EndEffector::basket_intake() { set_volts(127); }

void EndEffector::set_volts(int voltage) {
  upper_motor.move(voltage);
  lower_motor.move(voltage);
}

void EndEffector::stop() { set_volts(0); }

void EndEffector::run() {
  bool manual_control = false;
  if (controller.get_digital(
          CONTROLLER_BUTTONS::ENDEFFECTOR::DISABLE_COLOR_SORTING)) {
    manual_control = true;
  } else {
    eject_bottom = should_eject_L2();
    eject_top = should_eject_L3();
    manual_control = false;
  }

  if (controller.get_digital(CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_MID) &&
      controller.get_digital(CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_HIGH)) {
    basket_intake();
  } else if (controller.get_digital(
                 CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_HIGH)) {
    score_L3();

    if (!manual_control && eject_top) {
      upper_motor.move(127);
    }
  } else if (controller.get_digital(
                 CONTROLLER_BUTTONS::ENDEFFECTOR::SCORE_MID)) {
    score_L2();

    if (!manual_control && eject_bottom) {
      lower_motor.move(127);
    }
  } else if (controller.get_digital(CONTROLLER_BUTTONS::INTAKE::INTAKE)) {
    index();
  } else {
    // Reset stop flag when button is released
    stop_for_indexing = false;
    stop();
  }
}