#include "definitions.hpp"

//Class constructor for our chassis.  Allows us to insert the motor ports easier than making them ourselves
Drive chassis(
  // Left side motors. Negative means that the motor is reversed
  {15, -16, -17}

  // Right side motors.  Negative means that the motor is reversed
  ,{-18, 19, 20}

  // Port of our inertial sensor
  ,14

  //The size of our wheels
  ,3.25

  //What sort of motors we have (600 RPM = blue, 200 RPM = green, 100 RPM = red)
  ,600

  //Ratio that we have for our drivetrain
  ,1.666
);

//Intake and kicker with their respective cartiages
Motor intake(-5, MOTOR_GEAR_BLUE);
Motor kicker(12, MOTOR_GEAR_RED);

//The wings and hang are connected to pneumatics, which are basically "On/Off" switches.  As such, they are declared with a letter (as well, the letter is because of them using a differnet input system than everything else)
Piston wings('A');
Piston hang('B');
