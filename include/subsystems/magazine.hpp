#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/distance.hpp"
#include "pros/optical.hpp"
#include "electronics/vision.hpp"

class Magazine {
public:
  Magazine();
  void set_volts(int voltage);
  void run();
  void init();
  void outtake();
  void basket_outtake();
  void intake();
  void stop();

  pros::Motor lower_motor;
  pros::Motor upper_motor;
};
