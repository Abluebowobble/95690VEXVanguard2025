#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/distance.hpp"
#include "pros/optical.hpp"

class Intake {
public:
  Intake();
  void set_volts(int voltage);
  void run();
  void init();
  void outtake();
  void basket_outtake();
  void intake();
  void stop();
  void toggle();

  pros::adi::Pneumatics basket_pneumatic;
  pros::Motor upper_motor;
  pros::Motor lower_motor;
  bool is_open;
};
