#include "main.h"
#include "constants.hpp"
#include "electronics/selector.hpp"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/endeffector.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/lil_will.hpp"
#include "subsystems/wing.hpp"
// tallest 1
// second tallest 2
//  port 9 closer to intake
//  port 10

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

// ASSETS

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

void right_side_auto() {
  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

  // v2
  chassis.setPose(0, 0, 0);

  // get first 3 balls
  subsystems.intake.intake();
  chassis.moveToPoint(6, 30, 5000, {.maxSpeed = 55}); // test

  chassis.waitUntil(23);
  subsystems.lilWill.will_pneumatic.extend();

  // move backwards
  chassis.moveToPoint(6, 26, 5000, {.forwards = false, .maxSpeed = 80});
  chassis.waitUntilDone();
  subsystems.lilWill.will_pneumatic.retract();

  // turn to middle
  // chassis.turnToHeading(-41, 1000);

  // turn to match loader
  chassis.turnToHeading(132, 1500);

  // go to ml
  subsystems.lilWill.will_pneumatic.extend();
  chassis.moveToPoint(34, -9, 2000);
  chassis.turnToHeading(180, 1000);

  // do this together hopefully, run in to match loader
  chassis.moveToPoint(34, -30, 700, {.minSpeed = 127});
  chassis.waitUntilDone();
  pros::delay(1000);
  subsystems.endeffector.index();
  pros::delay(100);
  subsystems.endeffector.stop();

  // ml delay
  pros::delay(1500);

  // score, chassis timeout delay
  chassis.moveToPoint(37, 70, 10000, {.forwards = false, .maxSpeed = 120});

  // set up hood
  chassis.waitUntil(6);
  subsystems.lilWill.will_pneumatic.retract();
  subsystems.lilWill.hood_pneumatic.extend();
  subsystems.endeffector.score_L3();
}

void left_side_auto() {

  int MIDDLE_SCORE_DELAY = 1000;
  int MATCH_LOAD_DELAY = 700;
  int SCORE_DELAY = 1500;

  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

  // v2
  chassis.setPose(0, 0, 0);

  // get first 3 balls
  subsystems.intake.intake();
  chassis.moveToPoint(-8, 28, 5000, {.maxSpeed = 60}); // test

  chassis.waitUntil(20);
  subsystems.lilWill.will_pneumatic.extend();

  // move backwards
  // chassis.moveToPoint(-3, 25, 5000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToHeading(-135, 1000);

  // lift lil will
  chassis.waitUntilDone();
  subsystems.lilWill.will_pneumatic.retract();

  // turn to middle goal
  chassis.moveToPoint(-4, 30, 1000, {.forwards = false});
  chassis.turnToHeading(-135, 1000);

  // score
  chassis.waitUntilDone();
  subsystems.endeffector.score_L3();

  // middle score time
  pros::delay(MIDDLE_SCORE_DELAY);
  subsystems.endeffector.stop();

  // backup
  chassis.moveToPoint(-7, 16, 700);

  // turn to match loader
  chassis.turnToHeading(222, 700);

  // go to ml
  subsystems.lilWill.will_pneumatic.extend();
  chassis.moveToPoint(-34, -9, 2000);
  chassis.turnToHeading(180, 1000);

  // do this together hopefully, run in to match loader
  chassis.moveToPoint(-33, -30, 700, {.minSpeed = 100});

  // index
  chassis.waitUntilDone();
  pros::delay(1000);
  subsystems.endeffector.index();
  pros::delay(100);
  subsystems.endeffector.stop();

  // ml delay
  pros::delay(MATCH_LOAD_DELAY);

  // score, chassis timeout delay
  chassis.moveToPoint(-33, 70, 700,
                      {.forwards = false, .maxSpeed = 100});

  // set up hood
  chassis.waitUntil(6);
  subsystems.lilWill.will_pneumatic.retract();
  subsystems.lilWill.hood_pneumatic.extend();
  subsystems.endeffector.score_L3();
  pros::delay(SCORE_DELAY);

  // move back
  chassis.moveToPoint(-32, -9, 1000);
  //
  chassis.moveToPoint(-32, 70, 1000, { .forwards=false, .minSpeed = 100});
}

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
void autonomous() { right_side_auto(); }

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

      pros::lcd::print(7, "Upper voltage: %.1fV, Lower voltage: %.1fV",
                       subsystems.intake.motor.get_voltage() / 1000.0,
                       subsystems.intake.motor.get_voltage() / 1000.0);

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
  // subsystems.lilWill.set_start();

  colour_debug();
  subsystems.endeffector.stop_for_indexing = false;

  while (true) {
    // Drivetrain control
    subsystems.drivetrain.drive();

    // EndEffector control
    subsystems.endeffector.run();

    // intake control
    subsystems.intake.run();

    // Intake
    subsystems.intake.run();

    // lilwill
    subsystems.lilWill.run();

    // wing
    subsystems.wing.run();

    // if (globals::controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
    //   simple_auton();
    // }

    // if (globals::controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {

    //   lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

    //   chassis.setPose(0, 0, 0);
    //   chassis.follow(stra_txt, 15, 1000000);
    // }

    pros::delay(20);
  }
}