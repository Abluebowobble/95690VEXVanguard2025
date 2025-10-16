#pragma once

#include "lemlib/api.hpp" // IWYU pragma: keep∏

class Intake {
public:
  Intake();
  void run();
  void toggle();
private:
  pros::adi::Pneumatics intake_pneumatic;
};
