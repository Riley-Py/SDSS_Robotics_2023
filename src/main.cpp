/* //Description: VEX Robotics Code for 29295C Stratford Robotics
   //Date of last modification: Feburary 5th, 2024
   //Programmers (alphabetical by last name): Riley Cant, Sebastien Chung, Devan Hu
   //Libraries utilized: EZ-Template, GIF-PROS, PROS 3, LVGL
*/


//Includes all necessary libraries needed
#include "main.h"
#include "definitions.hpp"
#include "gif-pros/gifclass.hpp"


//Names for buttons on button matrix
static const char * btn_names[] = {"Autonomous (Defensive)", "Autonomous (Offensive)", "\n","Skills", "Elimination", ""};

//Gets the autonomous selected from the autonomous selector
string autonSelected;

//Initalizes the controls for the robot
void controls();

//The function that is called whenever a button is pressed
static lv_res_t callback(lv_obj_t * btnmatrix, const char* name) {
  master.print(0, 0, "%s", name);
  autonSelected = name;
  return LV_RES_OK;
}

//The UI itself
void ui () {

  //Styles for the toggled (pressed) state of a button as well as the style of the button matrix
  static lv_style_t style_bg;
  static lv_style_t pressed_state;
  
  //Customizing the style of the buttons to be black
  lv_style_copy(&style_bg, &lv_style_plain);
  style_bg.body.main_color = LV_COLOR_HEX(0x000000);
  style_bg.body.grad_color = LV_COLOR_HEX(0x000000);
  style_bg.body.border.color = LV_COLOR_HEX(0xFFFFFF);
  

  //Cutsomizing the toggled state of the buttons to be yellow to match our school colors of black and yellow
  lv_style_copy(&pressed_state, &lv_style_btn_tgl_rel);
  pressed_state.body.main_color = LV_COLOR_HEX(0xE2C044);
  pressed_state.body.grad_color = LV_COLOR_HEX(0xE2C044);

  //Sets up button matrix
  lv_obj_t * button_matrix = lv_btnm_create(lv_scr_act(), NULL);

  //Buttons are created with respect to the list of names above
  lv_btnm_set_map(button_matrix, btn_names);

  //Sets up toggling to be true
  lv_btnm_set_toggle(button_matrix, true, lv_btnm_get_toggled(button_matrix));

  //Sets up what happens when a button is pressed
  lv_btnm_set_action(button_matrix, callback);

  //Resizes button matrix
  lv_obj_set_size(button_matrix, 482, 240);

  //Sets the style of the background of the button matrix as well as the toggled state of the buttons
  lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BG, &style_bg);
  lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BTN_TGL_REL, &pressed_state);
}



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
  cata.set_brake_mode(MOTOR_BRAKE_COAST);
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
  
  //Sets the counter since this program has ran
  auto counter = millis();
  
  //How long that the driver control period is (60 seconds = 1 minute)
  int time = 60;
  
  //An infinite loop so that the controls can always be operated
  while(true) {

    //Puts the chassis into a standard remote control 
    chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    
    //Controls for the UI
    controls();
    
    //Subtracts the time when the counter divided by 1000 milliseconds (which is 1 second) doesn't produce a remainder (i.e. has exactly been one second)
    if (counter % 1000 == 0) {
      time--;
    }
    
    //Delays the process of the program in order to be accurate
    pros::delay(util::DELAY_TIME);
  }
}

//Numerous controls for the robot
void controls() {
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
  if (master.get_digital_new_press(DIGITAL_Y) && time <= 30) {
    hangState = !hangState;
    hang.set_value(hangState);
  }
}
