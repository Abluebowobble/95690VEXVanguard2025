#pragma once

#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "lemlib/pose.hpp"
#include "electronics/vision.hpp"

class EndEffector {
public:
  EndEffector();
  void score_L3();
  void score_L2();
  void basket_intake();
  void set_volts(int voltage);
  void run();
  void init();
  void stop();
  void set_L2_color(void* param);
  void set_L3_color(void* param);
  bool should_eject_L2();
  bool should_eject_L3();
  globals::SensorColors get_L2_color();
  globals::SensorColors get_L3_color();
  double get_L2_hue();
  double get_L3_hue(); 

  pros::Motor upper_motor;
  pros::Motor lower_motor;
  pros::ColorSensor L3_color_sensor;
  pros::ColorSensor L2_color_sensor;
  globals::SensorColors L2_color;
  globals::SensorColors L3_color;
  bool eject_bottom;
  bool eject_top;
  bool manual_control;
};
