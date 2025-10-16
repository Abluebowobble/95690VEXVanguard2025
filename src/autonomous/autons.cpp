#include "autonomous/auton.hpp"
#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h" // IWYU pragma: export
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <iostream>
#include <string>

using namespace globals;

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