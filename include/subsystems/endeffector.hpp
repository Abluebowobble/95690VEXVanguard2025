#pragma once

#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep∏
#include "lemlib/pose.hpp"
#include "electronics/vision.hpp"
#include "pros/adi.hpp"

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
  void should_eject_L2();
  void should_eject_L3();
  globals::SensorColors get_L2_color();
  globals::SensorColors get_L3_color();
  double get_L2_hue();
  double get_L3_hue(); 
  void index();
  void get_colors();

  pros::Motor upper_motor;
  pros::Motor lower_motor;
  pros::ColorSensor L3_color_sensor;
  pros::ColorSensor L2_color_sensor;
  globals::SensorColors L2_color = globals::SensorColors::NONE;
  globals::SensorColors last_L2_color = globals::SensorColors::NONE;
  globals::SensorColors L3_color;
  globals::SensorColors last_L3_color;
  bool eject_bottom;
  bool eject_top;
  bool manual_control;
  bool stop_for_indexing;

  
};
