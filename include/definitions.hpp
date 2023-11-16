#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "main.h"

Controller master(CONTROLLER_MASTER);

Motor leftA(15, MOTOR_GEAR_BLUE);
Motor leftB(-16, MOTOR_GEAR_BLUE);
Motor leftC(-17, MOTOR_GEAR_BLUE);

Motor rightA(-18, MOTOR_GEAR_BLUE);
Motor rightB(19, MOTOR_GEAR_BLUE);
Motor rightC(20, MOTOR_GEAR_BLUE);

MotorGroup leftMotors({leftA, leftB, leftC});
MotorGroup rightMotors({rightA, rightB, rightC});

Motor intake(6, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_DEGREES);

Motor cata(12,  MOTOR_GEAR_RED, false,  MOTOR_ENCODER_DEGREES);

Motor flywheelA(1,  MOTOR_GEAR_GREEN, false,  MOTOR_ENCODER_DEGREES);
Motor flywheelB(2,  MOTOR_GEAR_GREEN, true,  MOTOR_ENCODER_DEGREES);

Rotation cataRotationSensor(4);

#endif