#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep∏

class Hood {
public:
  Hood();
  void toggle();
  void run();
  void up();
  void down();

  pros::adi::Pneumatics hood_pneumatic;

};
