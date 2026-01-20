#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep∏

class LilWill {
public:
  LilWill();
  void toggle();
  void run();
  void up();
  void down();

  pros::adi::Pneumatics will_pneumatic;

};
