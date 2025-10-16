#include "main.h"
#include "constants.hpp"
#include "electronics/selector.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "subsystems/drivetrain.hpp"
#include "subsystems/endeffector.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/lil_will.hpp"
#include "subsystems/magazine.hpp"
// tallest 1
// second tallest 2
//  port 9 closer to intake
//  port 10

struct RobotSubsystems {
  Drivetrain drivetrain;
  Magazine magazine;
  EndEffector endeffector;
  Intake intake;
  LilWill lilWill;
} subsystems;

struct RobotScreen {
  SelectorScreen selector;
} screen;

// ASSETS
ASSET(isabellasstraightcode_txt)

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
  subsystems.magazine.init();
  subsystems.endeffector.init();

  pros::delay(100);

  // pros::Task colour_check([&]() {
  //   while (true) {
  //     globals::SensorColors l2_color = subsystems.endeffector.get_L2_color();
  //     globals::SensorColors l3_color = subsystems.endeffector.get_L3_color();

  //     double l2_hue = subsystems.endeffector.get_L2_hue();
  //     double l3_hue = subsystems.endeffector.get_L3_hue();

  //     const char *l2_str = (l2_color == globals::SensorColors::RED)    ?
  //     "RED"
  //                          : (l2_color == globals::SensorColors::BLUE) ?
  //                          "BLUE"
  //                                                                      :
  //                                                                      "NONE";
  //     const char *l3_str = (l3_color == globals::SensorColors::RED)    ?
  //     "RED"
  //                          : (l3_color == globals::SensorColors::BLUE) ?
  //                          "BLUE"
  //                                                                      :
  //                                                                      "NONE";

  //     pros::lcd::print(1, "L2:%s(%.0f) L3:%s(%.0f)", l2_str, l2_hue, l3_str,
  //                      l3_hue);

  //     pros::lcd::print(2, "Eject L2: %d | L3: %d",
  //                      subsystems.endeffector.should_eject_L2(),
  //                      subsystems.endeffector.should_eject_L3());

  //     pros::lcd::print(3, "Upper voltage: %.1f, Lower voltage: %.1f",
  //                      subsystems.magazine.upper_motor.get_voltage(),
  //                      subsystems.magazine.lower_motor.get_voltage());

  //     pros::delay(50);
  //   }
  // });
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
  // pid tuning
  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();
  chassis.calibrate();

  chassis.setPose(0, 0, 270);

  // chassis.moveToPoint(10, 0, 5000);
  chassis.turnToHeading(90, 5000);

  // jerry
  // chassis.setPose(0, 0, 0);
  // chassis.follow(isabellasstraightcode_txt, 15, 100000);
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

  // Start color sensor debug display task
  pros::Task colour_check([&]() {
    pros::delay(50);
    while (true) {
      globals::SensorColors l2_color = subsystems.endeffector.get_L2_color();
      globals::SensorColors l3_color = subsystems.endeffector.get_L3_color();

      double l2_hue = subsystems.endeffector.get_L2_hue();
      double l3_hue = subsystems.endeffector.get_L3_hue();

      const char *l2_str = (l2_color == globals::SensorColors::RED)    ? "RED"
                           : (l2_color == globals::SensorColors::BLUE) ? "BLUE"
                                                                       : "NONE";
      const char *l3_str = (l3_color == globals::SensorColors::RED)    ? "RED"
                           : (l3_color == globals::SensorColors::BLUE) ? "BLUE"
                                                                       : "NONE";

      pros::lcd::print(5, "L2:%s(%.0f) L3:%s(%.0f)", l2_str, l2_hue, l3_str,
                       l3_hue);

      pros::lcd::print(6, "Eject L2: %d | L3: %d",
                       subsystems.endeffector.should_eject_L2(),
                       subsystems.endeffector.should_eject_L3());

      pros::lcd::print(7, "Upper voltage: %.1f, Lower voltage: %.1f",
                       subsystems.magazine.upper_motor.get_voltage(),
                       subsystems.magazine.lower_motor.get_voltage());

      pros::delay(50);
    }
  });

  // while (true) {
  //   subsystems.endeffector.set_volts(
  //       globals::controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  //   subsystems.magazine.set_volts(
  //       globals::controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

  //   pros::delay(20);  
  // }

  while (true) {
    // Drivetrain control
    subsystems.drivetrain.drive();

    // EndEffector control
    subsystems.endeffector.run();

    // Magazine control
    subsystems.magazine.run();

    // Intake
    subsystems.intake.run();

    // lilwill
    subsystems.lilWill.run();

    // if (globals::controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
    //   lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();
    //   chassis.calibrate();

    //   chassis.setPose(0, 0, 0);

    //   // chassis.moveToPoint(10, 0, 5000);
    //   chassis.turnToHeading(90, 5000);
    // }

    // if (globals::controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
    //   lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();
    //   chassis.calibrate();
    //   chassis.setPose(34, 48, 89.381);
    //   chassis.follow(isabellasstraightcode_txt, 15, 100000);
    // }

  pros::delay(20);
  }
}