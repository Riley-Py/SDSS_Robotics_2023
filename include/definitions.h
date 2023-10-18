#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "main.h"

Controller master(E_CONTROLLER_MASTER);

Motor rightA(19, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rightB(20, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor_Group rightMotors({rightA, rightB});

Motor leftA(16, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor leftB(17, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);
Motor_Group leftMotors({leftA, leftB});

Motor leftTop(15, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rightTop(18, E_MOTOR_GEAR_BLUE, true, E_MOTOR_ENCODER_DEGREES);

Motor cata(12, E_MOTOR_GEAR_RED, false, E_MOTOR_ENCODER_DEGREES);

Motor aaa(1, E_MOTOR_GEAR_GREEN, false, E_MOTOR_ENCODER_DEGREES);
Motor bbb(2, E_MOTOR_GEAR_GREEN, true, E_MOTOR_ENCODER_DEGREES);

ADIDigitalIn cataLimit('a');

#endif