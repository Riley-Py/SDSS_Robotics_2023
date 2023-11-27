

#define DEFINITIONS_HPP
#ifdef DEFINITIONS_HPP

#include "main.h"

//Definitions for certain values
adi::Pneumatics wings('A', false, false);
adi:: Pneumatics intake_extender ('B', false, false);
Motor intake(6, MotorGears::blue, MotorUnits::degrees);
Rotation rot_sen(4);
Motor cata(12, MotorGears::red, MotorUnits::degrees);

double degrees_cata = 5950;


#endif