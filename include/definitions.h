#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "main.h"

Controller master(CONTROLLER_MASTER);

Motor rightA(19, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_DEGREES);
Motor rightB(20, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_DEGREES);
Motor_Group rightMotors({rightA, rightB});

Motor leftA(16,  MOTOR_GEAR_BLUE, true,  MOTOR_ENCODER_DEGREES);
Motor leftB(17,  MOTOR_GEAR_BLUE, true,  MOTOR_ENCODER_DEGREES);
Motor_Group leftMotors({leftA, leftB});

Motor leftTop(15,  MOTOR_GEAR_BLUE, false,  MOTOR_ENCODER_DEGREES);
Motor rightTop(18,  MOTOR_GEAR_BLUE, true,  MOTOR_ENCODER_DEGREES);

Motor cata(12,  MOTOR_GEAR_RED, false,  MOTOR_ENCODER_DEGREES);

Motor flywheelA(1,  MOTOR_GEAR_GREEN, false,  MOTOR_ENCODER_DEGREES);
Motor flywheelB(2,  MOTOR_GEAR_GREEN, true,  MOTOR_ENCODER_DEGREES);

ADIDigitalIn cataLimit('a');

Rotation cataRotationSensor(4);

#endif