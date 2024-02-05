#include "main.h"
#include "definitions.hpp"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


constexpr int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
constexpr int TURN_SPEED  = 90;
constexpr int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}

void offensiveZoneQual() {
  chassis.pid_drive_set(30, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  intake.move_voltage(-12000);

  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  chassis.pid_wait_until(5);
  intake.brake();
  chassis.pid_wait();
  
  chassis.pid_drive_set(-15, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-135, TURN_SPEED);
  chassis.pid_wait_until(-105);
  wings.set_value(1);
  chassis.pid_wait();

  chassis.pid_turn_set(-200, TURN_SPEED);
  chassis.pid_wait();
    
  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  chassis.pid_wait_until(15);
  chassis.pid_turn_set(-155, TURN_SPEED);
  chassis.pid_wait();

  wings.set_value(0);

  chassis.pid_drive_set(40, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void defensiveZone() {
  intake.move_voltage(-12000);
  chassis.pid_drive_set(7, DRIVE_SPEED, false);
  chassis.pid_wait();
  intake.brake();

  chassis.pid_turn_set(180, TURN_SPEED);
  chassis.pid_wait();

  intake.move_voltage(12000);
  chassis.pid_drive_set(30, DRIVE_SPEED, true);
  chassis.pid_wait_until(10);
  intake.brake();
  chassis.pid_wait();

  chassis.pid_turn_set(225, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(34, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(270, TURN_SPEED);
  chassis.pid_wait();
  
  intake.move_voltage(-12000);
  chassis.pid_drive_set(15, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.brake();

  chassis.pid_drive_set(-15, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(225, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-20, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(270, TURN_SPEED);
  wings.set_value(1);
  chassis.pid_wait();

  chassis.pid_turn_set(200, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  chassis.pid_wait_until(15);
  chassis.pid_turn_set(405, 127);
  chassis.pid_wait();

  wings.set_value(0);
  
  chassis.pid_drive_set(22, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(360, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24, DRIVE_SPEED, true);
  chassis.pid_wait();
}
