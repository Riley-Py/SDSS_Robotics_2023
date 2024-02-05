#include "main.h"
#include "definitions.hpp"
#include "gif-pros/gifclass.hpp"



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void controls();
void controller_ui();

static const char * btn_names[] = {"Autonomous (Defensive)", "Autonomous (Offensive)", "\n","Skills", "Elimination", ""};
int button_pressed = 0;

static lv_res_t callback(lv_obj_t * btnmatrix, const char* name) {
  
  
  master.print(0, 0, "%s", name);

  

  return LV_RES_OK;
}

void ui () {

  static lv_style_t style_bg;
  static lv_style_t pressed_state;

  lv_style_copy(&style_bg, &lv_style_plain);
  style_bg.body.main_color = LV_COLOR_HEX(0x000000);
  style_bg.body.grad_color = LV_COLOR_HEX(0x000000);
  style_bg.body.border.color = LV_COLOR_HEX(0xFFFFFF);
   
  lv_style_copy(&pressed_state, &lv_style_btn_tgl_rel);
  pressed_state.body.main_color = LV_COLOR_HEX(0xE2C044);
  pressed_state.body.grad_color = LV_COLOR_HEX(0xE2C044);


  //Sets up button matrix
  lv_obj_t * button_matrix = lv_btnm_create(lv_scr_act(), NULL);
  lv_btnm_set_map(button_matrix, btn_names);
  lv_btnm_set_toggle(button_matrix, true, lv_btnm_get_toggled(button_matrix));
  lv_btnm_set_action(button_matrix, callback);
  lv_obj_set_size(button_matrix, 482, 240);

  lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BG, &style_bg);
  lv_btnm_set_style(button_matrix, LV_BTNM_STYLE_BTN_TGL_REL, &pressed_state);
  
  

}
void initialize() {
  master.clear();
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  default_constants(); // Set the drive to your own constants from autons.cpp!
  chassis.set_curve_default(3, 3);
  chassis.set_joystick_threshold(3);

  chassis.initialize();

  cata.set_brake_mode(MOTOR_BRAKE_COAST);
  intake.set_brake_mode(MOTOR_BRAKE_COAST);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  ui();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  Gif* gif = new Gif("/usd/fish.gif", lv_scr_act());
  master.clear();

  while(true) {
    chassis.arcade_standard(ez::SPLIT);
    controller_ui(); // Standard split arcade
    controls();

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
  
  //Moves kicker (cata)
  if(master.get_digital(DIGITAL_L1)) {
    cata.move_voltage(12000);
  }
  else {
    cata.move_voltage(0);
  }
  
  //Activates hang (for testing; in a real match, I would get a millis timer so that the driver can't accidentally hit it unitl the time is 30 seconds)
  if (master.get_digital_new_press(DIGITAL_Y)) {
    hangState = !hangState;
    hang.set_value(hangState);
  }

}

void controller_ui() {
  master.print(0, 0, "K Temp %d", cata.get_temperature());
  master.print(0, 1, "B Cap: %d", pros::battery::get_capacity());

  

}
