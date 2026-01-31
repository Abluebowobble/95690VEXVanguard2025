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
  case 3:;
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
  chassis.turnToHeading(136, 1500);

  // go to ml
  subsystems.lilWill.will_pneumatic.extend();
  chassis.moveToPoint(35, -9, 2000);
  chassis.turnToHeading(180, 1000);

  // do this together hopefully, run in to match loader
  chassis.moveToPoint(35, -60, 1000, {.minSpeed = 110});
  chassis.waitUntilDone();
  pros::delay(1000);
  subsystems.endeffector.index();

  chassis.moveToPoint(34, -60, 200, {.minSpeed = 50});
  pros::delay(50);
  chassis.moveToPoint(34, -60, 200, {.minSpeed = 90});
  pros::delay(50);

  // ml delay
  pros::delay(700);
  
  // score, chassis timeout delay
  chassis.moveToPoint(43, 70, 10000, {.forwards = false, .maxSpeed = 90});

  // set up hood
  chassis.waitUntil(3);
  subsystems.lilWill.will_pneumatic.retract();
  pros::delay(250);
  subsystems.endeffector.score_L3();
  chassis.moveToPoint(43, 70, 5000, {.forwards = false, .maxSpeed = 70});
  subsystems.intake.intake();
  subsystems.endeffector.score_L3();

  // chassis.moveToPoint(9, 9, 10000, {.forwards = true, .minSpeed = 80});
}

void move_forwards() {
  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

  subsystems.intake.intake();

  chassis.setPose(0, 0, 0);
  subsystems.drivetrain.get_left_motors().move(127);
  subsystems.drivetrain.get_right_motors().move(127);
  pros::delay(2000);


  subsystems.drivetrain.get_left_motors().move(0);
  subsystems.drivetrain.get_right_motors().move(0);
}

void test() {
  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

  chassis.setPose(0, 0, 0);

  subsystems.lilWill.will_pneumatic.extend();
  pros::delay(1000);
  subsystems.lilWill.will_pneumatic.retract(); 
  pros::delay(1000);

  subsystems.wing.toggle();
  pros::delay(1000);
  subsystems.wing.toggle();
  pros::delay(1000);

  subsystems.intake.basket_pneumatic.toggle(); 
  pros::delay(1000);
  subsystems.intake.basket_pneumatic.toggle();
  pros::delay(1000);
}

void skills_auto() {
  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

  chassis.setPose(0, 0, 0);
  
  subsystems.intake.intake();
  
  subsystems.lilWill.will_pneumatic.retract();
  
  chassis.moveToPoint(0, 12, 2000, {.maxSpeed = 60});
  chassis.waitUntilDone();
  
  chassis.turnToHeading(45, 1000);
  chassis.waitUntilDone();
  
  chassis.moveToPoint(17, 29, 3000, {.maxSpeed = 40});
  chassis.waitUntilDone();
  
  subsystems.lilWill.will_pneumatic.extend();
  pros::delay(300);
  
  chassis.moveToPoint(14, 26, 2000, {.forwards = false, .maxSpeed = 50});
  chassis.waitUntilDone();
  
  pros::delay(2000);
  
  // Release goal
  subsystems.lilWill.will_pneumatic.retract();
  pros::delay(200);
  
  chassis.turnToHeading(-45, 1000);
  chassis.waitUntilDone();
  
  chassis.moveToPoint(-10, 0, 4000, {.maxSpeed = 50});
  chassis.waitUntilDone();
  
  chassis.moveToPoint(-20, -10, 3000, {.maxSpeed = 45});
  chassis.waitUntilDone();
  
  chassis.turnToHeading(-135, 1000);
  chassis.waitUntilDone();
  
  chassis.moveToPoint(-28, -28, 3000, {.maxSpeed = 40});
  chassis.waitUntilDone();
  
  subsystems.lilWill.will_pneumatic.extend();
  pros::delay(300);

  chassis.moveToPoint(-25, -25, 1500, {.forwards = false, .maxSpeed = 50});
  chassis.waitUntilDone();
  
  pros::delay(1500);
  
  subsystems.lilWill.will_pneumatic.retract();
  pros::delay(200);

  chassis.turnToHeading(180, 1000);
  chassis.waitUntilDone();
  
  chassis.moveToPoint(-30, -50, 3000, {.maxSpeed = 55});
  chassis.waitUntilDone();
  
  chassis.moveToPoint(-10, -60, 3000, {.maxSpeed = 55});
  chassis.waitUntilDone();
  
  chassis.moveToPoint(20, -60, 3000, {.maxSpeed = 55});
  chassis.waitUntilDone();
  
  chassis.moveToPoint(35, -50, 3000, {.maxSpeed = 55}); 
  chassis.waitUntilDone();
  chassis.turnToHeading(135, 1000);
  chassis.waitUntilDone();
  
  chassis.moveToPoint(42, -28, 3000, {.maxSpeed = 40});
  chassis.waitUntilDone();
  
  subsystems.lilWill.will_pneumatic.extend();
  pros::delay(300);

  pros::delay(2000);
  
  subsystems.intake.stop();
}

void left_side_auto() {

  int MIDDLE_SCORE_DELAY = 800;
  int MATCH_LOAD_DELAY = 700;
  int SCORE_DELAY = 1500;

  lemlib::Chassis &chassis = subsystems.drivetrain.get_chassis();

  // v2
  chassis.setPose(0, 0, 0);

  // get first 3 balls
  subsystems.intake.intake();
  chassis.moveToPoint(-8, 28, 5000, {.maxSpeed = 60});

  chassis.waitUntil(20);
  subsystems.lilWill.will_pneumatic.extend();

  // move backwards
  // chassis.moveToPoint(-3, 25, 5000, {.forwards = false, .maxSpeed = 80});
  chassis.turnToHeading(-135, 1000);

  // lift lil will
  chassis.waitUntilDone();
  subsystems.lilWill.will_pneumatic.retract();

  // turn to middle goal
  chassis.moveToPoint(-2, 23, 1000, {.forwards = false});
  chassis.turnToHeading(-135, 1000);

  // score
  chassis.waitUntilDone();
  subsystems.endeffector.score_L3();

  // middle score time
  pros::delay(MIDDLE_SCORE_DELAY);
  subsystems.endeffector.stop();

  // go to ml
  chassis.moveToPoint(-36, -9, 2000, {.forwards = false});
  chassis.waitUntilDone();
  subsystems.lilWill.will_pneumatic.extend();
  
  chassis.turnToHeading(200, 1000);

  // do this together hopefully, run in to match loader
  chassis.moveToPoint(-35, -60, 200, {.minSpeed = 90});

  chassis.moveToPoint(-35, -60, 200, {.minSpeed = 90});
  pros::delay(100);
  chassis.moveToPoint(-35, -60, 200, {.minSpeed = 90});
  pros::delay(100);

  // index
  chassis.waitUntilDone();
  pros::delay(800);
  subsystems.endeffector.index();
  pros::delay(100);
  subsystems.endeffector.stop();

  // ml delay
  pros::delay(MATCH_LOAD_DELAY);
  
  // score, chassis timeout delay
  chassis.moveToPoint(-35, 70, 700,
                      {.forwards = false, .maxSpeed = 100});

  // set up hood
  chassis.waitUntil(7);
  subsystems.lilWill.will_pneumatic.retract();
  subsystems.endeffector.score_L3();
  pros::delay(SCORE_DELAY);
}