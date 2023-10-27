#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "main.h"
#include "drive.hpp"

Controller master(CONTROLLER_MASTER);

sdss_robotics_c::Drive drivetrain({15, -16, -17}, {-18, 19, 20}, E_MOTOR_GEAR_BLUE, E_MOTOR_BRAKE_COAST);

Motor intake(6, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_DEGREES);

Motor cata(12,  MOTOR_GEAR_RED, false,  MOTOR_ENCODER_DEGREES);

Motor flywheelA(1,  MOTOR_GEAR_GREEN, false,  MOTOR_ENCODER_DEGREES);
Motor flywheelB(2,  MOTOR_GEAR_GREEN, true,  MOTOR_ENCODER_DEGREES);

Rotation cataRotationSensor(4);

#endif