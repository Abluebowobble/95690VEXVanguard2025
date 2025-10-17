#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep∏

class LilWill {
public:
  LilWill();
  void toggle();
  void set_start();
  void run();
  void up();
  void down();

private:
  pros::adi::Pneumatics will_pneumatic;
  pros::adi::Pneumatics hood_pneumatic;
  bool is_set_for_start;
  bool is_down;

};
