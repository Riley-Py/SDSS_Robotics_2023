/* //Description: VEX Robotics Code for 29295C Stratford Robotics
   //Date of last modification: Feburary 5th, 2024
   //Programmers (alphabetical by last name): Riley Cant, Sebastien Chung, Devan Hu
   //Libraries utilized: EZ-Template, GIF-PROS, PROS 3, LVGL
*/

//Includes all necessary libraries needed
#include "main.h"
#include "definitions.hpp"
#include "ui.hpp"
#include "gif-pros/gifclass.hpp"

void controllerUiFn(void* param) {
  while(true) {
    master.set_text(0, 0, std::to_string(static_cast<int>(kicker.get_temperature())) + "°C");
    pros::delay(50);
    master.set_text(1, 0, std::to_string(static_cast<int>(battery::get_capacity())) + "%");
    pros::delay(50);
    master.set_text(2, 0, std::to_string(static_cast<int>(millis() - reinterpret_cast<int>(param)) / 1000) + "s");
    pros::delay(50);
  }
}

//Initalizes the controls for the robot
void controls(int startTime);

//Initializes when the program is selected
void initialize() {

  //Clears the screen
  master.clear();

  //Sets the braking system for our PID controller, which allows us to have more control over it
  chassis.opcontrol_drive_activebrake_set(0); 

  //Sets up constants that are need for the PID controller for autonomous
  default_constants(); 

  //Sepcifies the joystick curve on the left/right side of the motors 
  chassis.opcontrol_curve_default_set(3, 3);
  
  //Specifiy the maximum curve that the joystick can go 
  chassis.opcontrol_joystick_threshold_set(3);

  //Disables adjusting the joystick curve via the buttons on the controller
  chassis.opcontrol_curve_buttons_toggle(false);
   
  //Initializes all necessary motors on the robot for moving in autonomous
  chassis.initialize();
  
  //Sets the motors to allow them to gradually stop, as opposed to holding them, which stops them immediately.  This results in the motors not burning out as quick (i.e. overheating)
  kicker.set_brake_mode(MOTOR_BRAKE_COAST);
  intake.set_brake_mode(MOTOR_BRAKE_COAST);
}

//Unecessary built-in PROS function for our case
void disabled() {}

//Initalizes the UI when connected to competition switch before it's switched to autonomous
void competition_initialize() {
  ui();
}

//After competition initialize, it goes to autonomous when connected to competition switch
void autonomous() {

  //Resets the target for the PID (i.e. which speed it needs to get, what distance it needs to go with that target speed) to 0
  chassis.pid_targets_reset();

  //Resets the inertial sensor's position to 0 as the PID controller uses the inertial to track rotation and acceleration 
  chassis.drive_imu_reset();

  //Calibrates the motors to get them ready for autonomous
  chassis.drive_sensor_reset(); 

  //Sets the motors to the hold position, which in a PID system, is important as you don't want to continue going for a bit before stopping; you want to stop immediately
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); 
  
  //Based on what was chosen, it is associated with a different autonomous routine (to see the autonomous routines, see "autons.cpp")
  if(autonSelected == "Autonomous (Offensive)") {
    offensiveZoneQual();
  }
  else if (autonSelected == "Autonomous (Defensive)") {
    //...
  }
  else if (autonSelected == "Skills") {
    //...
  }
  else if (autonSelected == "Elimination") {
    //...
  }
}

//Driver control period
void opcontrol() {

  //After autonomous, you have to set the drivetrain back to coast so that the motors don't burn out
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  //Places a fish GIF on the brain screen because...we wanted to be intimidating to the opponents.  Fear the villainous fish!
  Gif* gif = new Gif("/usd/fish.gif", lv_scr_act());

  //Clears controller screen for controller UI (IN PROGRESS AS OF WRITING)
  master.clear();

  auto startTime = millis();

  Task controllerUi(controllerUiFn, (void*)startTime);
  
  //An infinite loop so that the controls can always be operated
  while(true) {

    //Puts the chassis into a standard remote control 
    chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    
    //Controls for the UI
    controls(startTime);
    //time = millis();
    
    //Delays the process of the program in order to be accurate
    pros::delay(50);
  }
}

//Numerous controls for the robot
void controls(int startTime) {
  //States of the wings and hang
  static bool wingsState{ false };
  static bool hangState { false };
  
  //Switches the wings in or out depending on the state
  if(master.get_digital_new_press(DIGITAL_A)) {
    wingsState = !wingsState;
    wings.set_value(wingsState);
  }

  //Moves intake
  if(master.get_digital(DIGITAL_R1)) {
    intake.move_voltage(-12000);
  } else if(master.get_digital(DIGITAL_R2)) {
    intake.move_voltage(12000);
  } else {
    intake.brake();
  }
  
  //Moves kicker 
  if(master.get_digital(DIGITAL_L1)) {
    kicker.move_voltage(11000);
  } else {
    kicker.brake();
  }
  
  //Activates hang only if it's the last 30 seconds so that there are no misprints
  if (master.get_digital_new_press(DIGITAL_Y) && millis() - startTime >= 30000) {
    hangState = !hangState;
    hang.set_value(hangState);
  }
}
