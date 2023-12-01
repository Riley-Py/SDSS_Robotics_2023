#include "main.h"
#include "definition.hpp"
#include "gif-pros/gifclass.hpp"

Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)

  {15, -16, -17}

  // Right Chassis Ports (negative port will reverse it!)

  ,{-18, 19, 20}

  // IMU Port
  ,9  

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.5

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.666

);

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

void lv_example_btn_1(void)
{
    
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle");
    lv_obj_center(label);

     
    

    
    


}

//Numerous controls for the robot
void controls(pros::Controller masta) {

     

      //R1 = Intake in; L1 = Intake out; L2 = Catapult
      //For the wings
      if (masta.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
          wings.toggle();
      }
      if (masta.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) {
        intake_extender.toggle();

      }
      if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
        intake.move_voltage(12000);


      }
      else if (masta.get_digital(E_CONTROLLER_DIGITAL_R2)) {
        intake.move_voltage(-12000);
      }
      else {
        intake.brake();
      }

    
};

//Cata controls
void cata_controls (pros::Controller masta_cata) {

   static bool cataFlag{ false };

    if(master.get_digital(DIGITAL_L1)) {
      cata.move_voltage(20000);
    }

    if(rot_sen.get_angle() < cataUpAngle) {
      cataFlag = false;
    }

    if(rot_sen.get_angle() >= cataDownAngle && !cataFlag) {
      cata.brake();
      cataFlag = true;
    }
	}






/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
 
  
  cata.set_brake_mode(MOTOR_BRAKE_COAST);
  intake.set_brake_mode(MOTOR_BRAKE_COAST);

   

  
  

  

  
  rot_sen.set_data_rate(5);

	
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

   lv_example_btn_1();
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
void autonomous() {}

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
  lv_obj_clean(lv_scr_act());
  
  while (true) {
    chassis.move_drive((std::clamp(static_cast <int> (master.get_analog(ANALOG_LEFT_Y)), -100, 100)), std::clamp(static_cast <int> (master.get_analog(ANALOG_RIGHT_X)), -100, 100), 3, 3, chassis.left_motors, chassis.right_motors);
    controls(master);
    cata_controls(master);
    pros::delay(20);
  }
}

