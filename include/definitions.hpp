#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "main.h"
#include "drive.hpp"
#include "pid.hpp" 

Controller master(CONTROLLER_MASTER);

sdss_robotics_c::Drive drivetrain({15, -16, -17}, {-18, 19, 20}, MotorGears::blue, MotorBrake::coast);

Motor intake(-6, MotorGears::blue, MotorUnits::degrees);

Motor cata(12, MotorGears::red, MotorUnits::degrees);

Motor flywheelA(1, MotorGears::green,  MotorUnits::degrees);
Motor flywheelB(-2, MotorGears::green,  MotorUnits::degrees);

Rotation cataRotationSensor(4);

pid::Pid p_controller(10, 2);

#endif