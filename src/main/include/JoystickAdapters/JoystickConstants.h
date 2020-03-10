//Constants used by joystick controllers


#include "units/units.h"

#pragma once

static const units::time::second_t sample_rate = 0.02_s;

   static constexpr double joystick_exponent = 2;
   static constexpr double deadband_limit = 0.05;
   static constexpr double speed_time_const = 0.01;
   static constexpr double turn_time_const = 0.01;
   static constexpr double lowgear_ratio = 0.5;

typedef enum{
    vision_drive=1,
    loader_off,
    loader_up,
    loader_down,
    winch_retract
} DriverButton;

typedef enum {
    acceleration=1,
    turn_left,
    turn_right
} DriverControl;


