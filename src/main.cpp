#include "main.h"
#include "constants.hpp"
#include "electronics/selector.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/endeffector.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/lil_will.hpp"
#include "subsystems/wing.hpp"

struct RobotSubsystems {
  Drivetrain drivetrain;
  EndEffector endeffector;
  Intake intake;
  LilWill lilWill;
  Wing wing;
} subsystems;

struct RobotScreen {
  SelectorScreen selector;
} screen;


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize();

  subsystems.drivetrain.init();
  subsystems.intake.init();
  subsystems.endeffector.init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  //  screen.selector.selector();
}

// Forward declaration of autonomous routines defined in autons.cpp
void right_side_auto();
void left_side_auto();

ASSET(stra_txt)

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() { 
  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();
  chassis.setPose(0, 0, 0);
  if (PID_CONSTANTS::TEST_TYPE::TEST_ANGULAR) {
    chassis.turnToHeading(180, 100000000);
  } else {
    chassis.moveToPose(0, 10, 0, 100000000);
  }
  // subsystems.endeffector.manual_control = true;
  // right_side_auto(); 
}

void snap_to_heading() {
  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();
  chassis.turnToHeading(0, 5000);
}

void colour_debug() {
  // // Start color sensor debug display task
  pros::Task colour_check([&]() {
    pros::delay(50);
    while (true) {
      globals::SensorColors l2_color = subsystems.endeffector.get_L2_color();
      globals::SensorColors l3_color = subsystems.endeffector.get_L3_color();
      globals::SensorColors last_l2_color = subsystems.endeffector.last_L2_color;
      globals::SensorColors last_l3_color = subsystems.endeffector.last_L3_color;

      double l2_hue = subsystems.endeffector.get_L2_hue();
      double l3_hue = subsystems.endeffector.get_L3_hue();

      const char *l2_str = (l2_color == globals::SensorColors::RED)    ? "RED"
                           : (l2_color == globals::SensorColors::BLUE) ? "BLUE"
                                                                       : "NONE";
      const char *l3_str = (l3_color == globals::SensorColors::RED)    ? "RED"
                           : (l3_color == globals::SensorColors::BLUE) ? "BLUE"
                                                                       : "NONE";
      const char *last_l2_str = (last_l2_color == globals::SensorColors::RED)    ? "RED"
                                : (last_l2_color == globals::SensorColors::BLUE) ? "BLUE"
                                                                                 : "NONE";
      const char *last_l3_str = (last_l3_color == globals::SensorColors::RED)    ? "RED"
                                : (last_l3_color == globals::SensorColors::BLUE) ? "BLUE"
                                                                                 : "NONE";

      // Display current and last colors
      pros::lcd::print(0, "L2: %s | Last L2: %s", l2_str, last_l2_str);
      pros::lcd::print(1, "L3: %s | Last L3: %s", l3_str, last_l3_str);
      pros::lcd::print(2, "Eject Bottom: %d | Eject Top: %d",
                       subsystems.endeffector.eject_bottom,
                       subsystems.endeffector.eject_top);

      // Get voltages for all 6 motors (in millivolts, convert to volts)
      std::vector<std::int32_t> left_voltages =
          subsystems.drivetrain.get_left_motors().get_voltage_all();
      std::vector<std::int32_t> right_voltages =
          subsystems.drivetrain.get_right_motors().get_voltage_all();

      pros::lcd::print(5, "L: %.1f %.1f %.1f | R: %.1f %.1f %.1f",
                       left_voltages[0] / 1000.0, left_voltages[1] / 1000.0,
                       left_voltages[2] / 1000.0, right_voltages[0] / 1000.0,
                       right_voltages[1] / 1000.0, right_voltages[2] / 1000.0);

      pros::lcd::print(6, "proximity L2: %d | L3: %d",
                       subsystems.endeffector.L2_color_sensor.get_proximity(),
                       subsystems.endeffector.L3_color_sensor.get_proximity());

      // pros::lcd::print(7, "Upper voltage: %.1fV, Lower voltage: %.1fV",
      //                  subsystems.intake.motor.get_voltage() / 1000.0,
      //                  subsystems.intake.motor.get_voltage() / 1000.0);

      pros::delay(50);
    }
  });
  // while (true) {
  //   subsystems.endeffector.set_volts(
  //       globals::controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  //   subsystems.intake.set_volts(
  //       globals::controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

  //   pros::delay(20);
  // }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  autonomous();
  // subsystems.lilWill.set_start();

  // colour_debug();
  // subsystems.endeffector.stop_for_indexing = false;

  // while (true) {
  //   // Drivetrain control
  //   subsystems.drivetrain.drive();

  //   // EndEffector control
  //   subsystems.endeffector.run();

  //   // intake control
  //   subsystems.intake.run();

  //   // Intake
  //   subsystems.intake.run();

  //   // lilwill
  //   subsystems.lilWill.run();

  //   // wing
  //   subsystems.wing.run();

  //   // if (globals::controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
  //   //   simple_auton();
  //   // }

  //   // if (globals::controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {

  //   //   lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

  //   //   chassis.setPose(0, 0, 0);
  //   //   chassis.follow(stra_txt, 15, 1000000);
  //   // }

  //   pros::delay(20);
  // }
}