#include "autonomous/auton.hpp"
#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: export
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "subsystems/drivetrain.hpp"
#include "subsystems/endeffector.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/lil_will.hpp"
#include "subsystems/wing.hpp"
#include <iostream>
#include <string>

using namespace globals;

// External reference to subsystems
extern struct RobotSubsystems {
  Drivetrain drivetrain;
  EndEffector endeffector;
  Intake intake;
  LilWill lilWill;
  Wing wing;
} subsystems;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_POS;
std::string Autonomous::autonName = "Red Positive";

constexpr int delay_constant = 1050;

// Takes in two parameters: The autonomous value as well as the puncher object.

void Autonomous::AutoDrive() {
  // Keep the switcher running while the controller down button has not been
  // pressed and the time period is not autonomous Compare the current auton
  // value to run the auton routine
  switch (Autonomous::auton) {
  case RED_NEG:
  case RED_POS:
  case RED_POS_LATE_RUSH:
  case BLUE_POS:
  case BLUE_POS_LATE_RUSH:
  case BLUE_NEG:
  case SKILLS:
    break;
  }
}

void Autonomous::AutonSwitcher(int autonNum) {
  switch (autonNum) {
  case 1:
    Autonomous::autonName = "Red Negative";
    Autonomous::auton = RED_NEG;
    break;
  case 2:
    Autonomous::autonName = "Red Positive Sweep";
    Autonomous::auton = RED_POS;
    break;
  case 3:
    Autonomous::autonName = "Red Positive Late Rush";
    Autonomous::auton = RED_POS_LATE_RUSH;
    break;
  case -1:
    Autonomous::autonName = "Blue Positive Sweep";
    Autonomous::auton = BLUE_POS;
    break;
  case -2:
    Autonomous::autonName = "Blue Positive Late Rush";
    Autonomous::auton = BLUE_POS_LATE_RUSH;
    break;
  case -3:
    Autonomous::autonName = "Blue Negative";
    Autonomous::auton = BLUE_NEG;
    break;
  case 0:
    Autonomous::autonName = "Skills";
    Autonomous::auton = SKILLS;
    break;
  }
  std::cout << "Current auton: " + Autonomous::autonName << std::endl;
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

  // ml delay
  pros::delay(3000);

  // score, chassis timeout delay
  chassis.moveToPoint(37, 70, 10000, {.forwards = false, .maxSpeed = 120});

  // set up hood
  chassis.waitUntil(6);
  subsystems.lilWill.will_pneumatic.retract();
  subsystems.endeffector.score_L3();
  chassis.moveToPoint(37, 70, 10000, {.forwards = true, .maxSpeed = 120});
  chassis.moveToPoint(37, 70, 10000, {.forwards = false, .maxSpeed = 120});

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
  subsystems.endeffector.score_L3();
  pros::delay(SCORE_DELAY);

  // move back
  chassis.moveToPoint(-32, -9, 1000);
  //
  chassis.moveToPoint(-32, 70, 1000, { .forwards=false, .minSpeed = 100});
}