#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep∏

class Wing {
public:
  Wing();
  void toggle();
  void run();

private:
  pros::adi::Pneumatics wing_pneumatic;
};
