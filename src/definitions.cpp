#include "definitions.hpp"

Drive chassis(
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {15, -16, -17}

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

Motor intake(6, MotorGears::blue);
Motor cata(12, MotorGears::red);

Rotation rotationSensor(4);

adi::Pneumatics wings('A', false);
adi::Pneumatics intakeExtender('B', false);

constexpr int cataUpAngle{ 18000 };
constexpr int cataDownAngle{ 22500 };