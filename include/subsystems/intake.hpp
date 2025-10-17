#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "pros/distance.hpp"
#include "pros/optical.hpp"
#include "electronics/vision.hpp"

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
  
// private:
  pros::Motor lower_motor;
  pros::Motor upper_motor;
  pros::adi::Pneumatics intake_pneumatic;
};
