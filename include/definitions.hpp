#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "main.h"

Controller master(CONTROLLER_MASTER);


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {15, -16, -19}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{-18, 19, 20}

  // IMU Port
  ,9

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.666
);

Motor intake(-6, MotorGears::blue);

Motor cata(12,  MotorGears::blue);

Rotation cataRotationSensor(4);

#endif