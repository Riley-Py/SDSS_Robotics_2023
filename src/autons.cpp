#include "main.h"
#include "definitions.hpp"

//Drive, turn, and swing speeds that are found to be accurate for the PID.  Anything higher and it makes it highly inaccurate
constexpr int DRIVE_SPEED = 110; 
constexpr int TURN_SPEED  = 90;
constexpr int SWING_SPEED = 90;

//Where the default PID values are determined.  This is where the tuning comes in
void default_constants() {

  //Sets the P, the I, and the D portion for the heading, the driving aspect (i.e. forwards and backwards), the turning aspect, and the swing aspect (a swing is when you curve around)

  /*A PID works sort of like this: 
     //The main goal of a PID system is to be as accurate as possible to a specific target.  
     //This done by using the "error" that sensors have collected (in this case, the inertial sensor) and trying to increase/decrease values ot minimize that "error".  
     //This "error" is the result of how off it is from the "setpoint" (i.e. If I wanted to go 90 KM/hr (the setpoint) and I was only going 50 KM/hr, then the error would be the setpoint (90) subtract the actual speed (50) to get an error of 40 KM/hr)
     //A PID controller has something called "gains" (the values that you adjust below) which adjusts the P, the I, and the D components of this controller
     //The "P" component (known as "proportional) is used to have a large reaction on the output (in my car allegory, the current speed) to bring it closer to the goal and minimize the error.
     //However, there comes a threshold where the "P" doesn't have much effect on minimizing the error, which is where the I comes in.
     //The "I" component (known as "integral") is calculated by using the I-gain and multiplying that by how many cylces the PID system goes and by the current error
     //This gain is then added to the I component and it compounds up (i.e. If I cycled 10 times a second and my I-gain is 10, then there would be 100 added to the I total.  However, the next time it runs, the I total would be 200, then 300, and so forth) 
     //The final component is the "D" component, and it predicts where the "current value" is going.  This prediction allows the D value to counteract the effects of the P and I so that there is no overshooting.  This is controlled via the D-gain.
     //Overall, a PID controller, when put together, is a robust controller capable of making autonomous routines as accurate as possible when the gains are tuned properly according to the robot specifications.
     */
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(14.5, 0, 30);
  chassis.pid_turn_constants_set(6.8, 0, 45);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}

/* //Autonomous routine for our offensive zone in qualification matches
void offensiveZoneQual() {

  //Go forward 30 inches
  chassis.pid_drive_set(30, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  //Turn 45 degrees counter-clockwise
  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();
  
  //Intake outtakes 
  intake.move_voltage(-12000);
  
  //Drives forward another 20 inches to make sure the triball is in
  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  //Waits until it passes 5 inches before doing the following below
  chassis.pid_wait_until(5);

  //Stops intake and waits until the robot is settled
  intake.brake();
  chassis.pid_wait();
  
  //Robot goes back 15 inches
  chassis.pid_drive_set(-15, DRIVE_SPEED, true);
  chassis.pid_wait();
  

  //Robot turns 135 degrees counter clockwise
  chassis.pid_turn_set(-135, TURN_SPEED);
  //Makes the robot wait until the turn is at 105 degrees before going
  chassis.pid_wait_until(-105);
  //Wings are opened
  wings.set(1);
  //Allows the robot to be settled
  chassis.pid_wait();
  
  //Turns to 200 degrees counter-clockwise
  chassis.pid_turn_set(-200, TURN_SPEED);
  //Waits until it is settled
  chassis.pid_wait();
  
  //Drives forward 20 inches
  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  //Waits until the robot is at 15 inches before turning 155 degrees counter clockwise
  chassis.pid_wait_until(15);
  chassis.pid_turn_set(-155, TURN_SPEED);
  //Waits until it is settled
  chassis.pid_wait();
  
  //Retracts the wings
  wings.set(0);

  
  //Drives forward to hit the hang bar for AWP and waits for the duration of the autonomous period
  chassis.pid_drive_set(40, DRIVE_SPEED, true);
  chassis.pid_wait();
} */

//Autonomous routine for our offensive zone in elimination rounds (GOOD)
void offensiveZoneElim() {

//Opens and closes wings after a certain time
wings.set(1);
pros::delay(300);
wings.set(0);

//Turn to face triball
chassis.pid_turn_set(11, TURN_SPEED);
pros::delay(250);

//Drive forward and takes triball in once the robot has moved 30 inches
chassis.pid_drive_set(64, DRIVE_SPEED, true);
chassis.pid_wait_until(30);
intake.move_voltage(12000);
chassis.pid_wait();

//Move back slightly to avoid hitting barrier when spinning
chassis.pid_drive_set(-4, DRIVE_SPEED, false);
chassis.pid_wait();
intake.brake();

//Spin to face goal
chassis.pid_turn_set(135, TURN_SPEED);
chassis.pid_wait();

//Push triballs in goal
wings.set(1);
chassis.pid_drive_set(30, DRIVE_SPEED, true);
chassis.pid_wait_until(15);
intake.move_voltage(-12000);
chassis.pid_wait();
wings.set(0);
intake.brake();

//Back out from the goal to avoid hitting it when spinning
chassis.pid_drive_set(-10, DRIVE_SPEED, false);
chassis.pid_wait();

//Spin to face next triball
chassis.pid_turn_set(288, TURN_SPEED);
chassis.pid_wait();

//Drive forward and intake triball
chassis.pid_drive_set(23, DRIVE_SPEED, true);
chassis.pid_wait_until(5);
intake.move_voltage(12000);
chassis.pid_wait();

//Turn to face match load bar
chassis.pid_turn_set(180, TURN_SPEED);
chassis.pid_wait();
intake.brake();

//Drive towards match load bar
chassis.pid_drive_set(42, DRIVE_SPEED, true);
chassis.pid_wait();

//turn towards goal and outtake triball
chassis.pid_turn_set(90, TURN_SPEED);
chassis.pid_wait();
intake.move_voltage(-12000);

//Wait until triball is out of intake
pros::delay(500);
intake.brake();

//Turn around in preparation to descore triball
chassis.pid_turn_relative_set(-45, TURN_SPEED);
chassis.pid_wait();

//Drive back and get wing over the barrier
wings.set(1);
chassis.pid_drive_set(-12, DRIVE_SPEED, true);
chassis.pid_wait();

//Turn back of bot towards to goal in preparation to descore triball and push others in goal
chassis.pid_turn_relative_set(35, TURN_SPEED);
chassis.pid_wait();

//Drive forward and de-score
chassis.pid_drive_set(20, DRIVE_SPEED, false);
chassis.pid_wait();

//Turn toward side of goal
wings.set(0);
chassis.pid_turn_relative_set(-40, TURN_SPEED);
chassis.pid_wait();

//Push triballs in side of goal
chassis.pid_drive_set(15, DRIVE_SPEED, true);
chassis.pid_wait();

} 

//Autonomous routine for our offensive zone in elimination rounds (NEW/GOOD)
void offensiveZoneQual() {
  intake.move_voltage(12000);
chassis.pid_drive_set(6, DRIVE_SPEED, false);
chassis.pid_wait();

intake.brake();
chassis.pid_drive_set(-18, DRIVE_SPEED, true);
chassis.pid_wait();

chassis.pid_turn_relative_set(-30, TURN_SPEED);
chassis.pid_wait();

chassis.pid_drive_set(-27, DRIVE_SPEED, true);
chassis.pid_wait_until(-6);
wings.set(1);
chassis.pid_wait();

chassis.pid_turn_relative_set(-195, TURN_SPEED);
wings.set(0);
chassis.pid_wait();

chassis.pid_drive_set(12, DRIVE_SPEED, true);
pros::delay(750);

chassis.pid_turn_relative_set(-45, TURN_SPEED);
pros::delay(750);

intake.move_voltage(-12000);
chassis.pid_drive_set(10, DRIVE_SPEED, false);
pros::delay(700);
chassis.pid_drive_set(-11, DRIVE_SPEED, true);
chassis.pid_wait();
intake.brake();

chassis.pid_drive_set(10, DRIVE_SPEED, false);
pros::delay(700);
chassis.pid_drive_set(-11, DRIVE_SPEED, true);
chassis.pid_wait();

chassis.pid_turn_relative_set(-135, TURN_SPEED);
chassis.pid_wait();

chassis.pid_drive_set(26, DRIVE_SPEED, true);
chassis.pid_wait();

chassis.pid_turn_relative_set(45, TURN_SPEED);
chassis.pid_wait();

chassis.pid_drive_set(32, DRIVE_SPEED, true);
chassis.pid_wait();
}

//TO-DO: For provincials, this needs to be done
/* // void skills() {

//   wings.set(1);
//   pros::delay(300);
//   wings.set(0);

//   chassis.pid_drive_set(5, DRIVE_SPEED, false, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(-90, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_drive_set(22, DRIVE_SPEED, false, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(25, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_drive_set(11, DRIVE_SPEED, false, true);
//   chassis.pid_wait();

//   chassis.pid_drive_set(-12, DRIVE_SPEED, false, true);
//   chassis.pid_wait();

//   chassis.pid_drive_set(12, DRIVE_SPEED, false, true);
//   chassis.pid_wait();

//   chassis.pid_drive_set(-11, DRIVE_SPEED, false, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(-45, TURN_SPEED);
//   chassis.pid_wait();

//   chassis.pid_drive_set(-5, DRIVE_SPEED, false, true);
//   chassis.pid_wait();

//   chassis.pid_turn_set(150, DRIVE_SPEED);
//   chassis.pid_wait();
   
// } */

//Autonomous routine for our defensive zone in elimination/qualification rounds (GOOD)
void defensiveZoneElim() {
  //pushes triball towards alley before rushing middle triball
  wings.set(1);
  pros::delay(300);
  wings.set(0);

  chassis.pid_drive_set(48, DRIVE_SPEED, true);
  chassis.pid_wait_until(30);
  intake.move_voltage(12000);
  chassis.pid_wait();
  intake.brake();

  chassis.pid_drive_set(-3, DRIVE_SPEED, false);
  chassis.pid_wait();

  chassis.pid_turn_set(72, TURN_SPEED);
  chassis.pid_wait();

  //pushes triballs over middle bar
  wings.set(1);
  chassis.pid_drive_set(23, DRIVE_SPEED, true);
  chassis.pid_wait_until(5);
  intake.move_voltage(-12000);
  chassis.pid_wait();

  wings.set(0);
  chassis.pid_drive_set(-12, DRIVE_SPEED, false);
  chassis.pid_wait();
  intake.brake();

  chassis.pid_turn_set(27, TURN_SPEED);
  chassis.pid_wait();

  //drive back to de-score
  chassis.pid_drive_set(-43, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-18, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-10, DRIVE_SPEED, false);
  chassis.pid_wait_until(-3);
  wings.set(1);
  chassis.pid_wait();

  chassis.pid_turn_set(-263, TURN_SPEED);
  wings.set(0);
  chassis.pid_wait();

//pushes triballs doewn the alley
  intake.move_voltage(-12000);
  chassis.pid_drive_set(25, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-288, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.brake();

  
  chassis.pid_drive_set(-31, DRIVE_SPEED, true);
  chassis.pid_wait();

}

void defensiveZoneQual() {
  //pushes triball towards alley before rushing middle triball
  wings.set(1);
  pros::delay(300);
  wings.set(0);

  chassis.pid_drive_set(48, DRIVE_SPEED, true);
  chassis.pid_wait_until(30);
  intake.move_voltage(12000);
  chassis.pid_wait();
  intake.brake();

  chassis.pid_drive_set(-3, DRIVE_SPEED, false);
  chassis.pid_wait();

  chassis.pid_turn_set(72, TURN_SPEED);
  chassis.pid_wait();

  //pushes triballs over middle bar
  wings.set(1);
  chassis.pid_drive_set(23, DRIVE_SPEED, true);
  chassis.pid_wait_until(5);
  intake.move_voltage(-12000);
  chassis.pid_wait();

  wings.set(0);
  chassis.pid_drive_set(-12, DRIVE_SPEED, false);
  chassis.pid_wait();
  intake.brake();

  chassis.pid_turn_set(27, TURN_SPEED);
  chassis.pid_wait();

  //drive back to de-score
  chassis.pid_drive_set(-43, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-18, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-10, DRIVE_SPEED, false);
  chassis.pid_wait_until(-3);
  wings.set(1);
  chassis.pid_wait();

  chassis.pid_turn_set(-263, TURN_SPEED);
  wings.set(0);
  chassis.pid_wait();

//pushes triballs doewn the alley
  intake.move_voltage(-12000);
  chassis.pid_drive_set(25, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-288, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20, DRIVE_SPEED, true);
  chassis.pid_wait();
  intake.brake();

  //Removed what you wanted, Sebastien :)


}

void skills_old_temp() {
  unsigned long kicker_timer;

  //NOTE: START ON DIAGONAL LIKE WE DID WITH CATAPULT BOT (USE THE SETTER TOOL)
  
  //Drives forward 28 inches forward
  chassis.pid_drive_set(28, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  

  //45 degrees clockwise
  chassis.pid_turn_relative_set(45, TURN_SPEED);
  chassis.pid_wait();
  

  //Moves intake and drives into net
  intake.move(12000);
  chassis.pid_drive_set(11, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  

  //Stops intake
  intake.move_voltage(0);
  

  //Drives back
  chassis.pid_drive_set(-12, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  

  //180 clockwise (to get wedge)
  chassis.pid_turn_relative_set(180, TURN_SPEED);
  chassis.pid_wait();
  
  //Drives into net again (makes sure the triballs are in)
  chassis.pid_drive_set(-18.5, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  
  //Drives back 15 inches
  chassis.pid_drive_set(15, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  

  //Turns again 180 degrees (kicker in right direction)
  chassis.pid_turn_relative_set(180, TURN_SPEED);
  chassis.pid_wait();
  

  //Drives back a few inches
  chassis.pid_drive_set(-6, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  
  //Turns 65 clockwise, relative to where the bot is now
  chassis.pid_turn_relative_set(65, TURN_SPEED);
  chassis.pid_wait();
  
  //Back 4 inches to make sure it's touching match load bar (this could work, this may not work :( )
  chassis.pid_drive_set(-4, DRIVE_SPEED, false, true);
  chassis.pid_wait();
  
  //Sets kicker timer as current amount of time passed
  kicker_timer = millis();
  

  //Kicker goes for 30 seconds, then stops
  while (millis() - kicker_timer >= 30000) {

    kicker.move_voltage(12000);
  }
  kicker.brake();

  //...INSTRUCTIONS TO SEBASTIEN/DEVAN: Test above first, then do the following in the short span of time (I know it isn't ideal, but hey, we just need something that works): 
  //1. Drive a bit on an angle
  //2. Turn
  //3. Get leftover triballs over barrier using wings and bot (do this two times)
  //4. Go over barrier without getting stuck
  //5. If 4 works, then push triballs in a few times
  //Here are my instructions for our temporary skills auton.  After CSAA, we are changing this






}