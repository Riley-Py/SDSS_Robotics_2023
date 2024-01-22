#include "main.h"
#include "definitions.hpp"
#include "gif-pros/gifclass.hpp"


//All of the labels
const char * collection_labels[] = {btn1, btn2, "\n", btn3, btn4, ""};

//Handles the events that the buttons may come up with
static void event_handler(lv_event_t* e) {

   lv_obj_t * button_pressed = lv_event_get_target(e);

   const char * id = lv_btnmatrix_get_btn_text(button_pressed, lv_btnmatrix_get_selected_btn(button_pressed));
   
   //Elimination
   if (strcmp(id, btn4) == 0) {

      auton_selector = 1;
   }

   //Auto defensive
   else if (strcmp(id, btn2) == 0) {
    auton_selector = 2;

   }
   
   //Skills
   else if (strcmp(id, btn3) == 0) {
    auton_selector = 3;

   }
   
   //Auto offensive
   else if (strcmp(id, btn1) == 0) {

    auton_selector = 4;
   }
}

void ui() {

  //Sets the background of the UI selector
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);
  
  
  // //Sets up the styles for text and buttons
  static lv_style_t button_style;
  static lv_style_t bg_style;
  static lv_style_t toggled_style;


  //Outline of buttons to be white
  lv_color_t outline_color = lv_color_make(255, 255, 255);
  
  //Initialize for button design
  lv_style_init(&button_style);
  lv_style_init(&bg_style);
  lv_style_init(&toggled_style);

  //Background for button
  lv_style_set_bg_opa(&button_style, LV_OPA_0);

  //Border/border color for buttons
  lv_style_set_border_width(&button_style, 2);
  lv_style_set_border_color(&button_style, outline_color);

  //Text for button matrix
  lv_style_set_pad_all(&button_style, 20);
  lv_style_set_text_color(&button_style, outline_color);

  //Toggled background (gold color)
  lv_style_set_bg_color(&toggled_style, lv_color_hex(0xFCAB10));

  //Background color for the button matrix
  lv_style_set_bg_color(&bg_style, lv_color_hex(0x003a57));

  //Creation/mapping of the button matrix
  lv_obj_t * collection_btn = lv_btnmatrix_create(lv_scr_act());
  lv_btnmatrix_set_map(collection_btn, collection_labels);

  //Sets width and height of button matrix
  
  lv_obj_set_size(collection_btn, 482, 240);

  //Centers the button matrix in the middle of the screen
  lv_obj_center(collection_btn);

  //Adds the styles
  lv_obj_add_style(collection_btn, &button_style, LV_PART_ITEMS);
  lv_obj_add_style(collection_btn, &bg_style, 0);
  lv_obj_add_style(collection_btn, &toggled_style, LV_PART_ITEMS | LV_STATE_CHECKED);

  //Sets the toggle features of the buttons
  lv_btnmatrix_set_btn_ctrl_all(collection_btn, LV_BTNMATRIX_CTRL_CHECKABLE);
  lv_btnmatrix_set_one_checked(collection_btn, true);

  //Adds event handler for the buttons
  lv_obj_add_event_cb(collection_btn, event_handler, LV_EVENT_CLICKED, NULL);

}




void initialize() {

  default_constants();
  chassis.initialize();
  chassis.set_active_brake(0.1); 
  chassis.set_joystick_threshold(3);
  
  kicker.set_brake_mode(MOTOR_BRAKE_COAST);
  intake.set_brake_mode(MOTOR_BRAKE_COAST);
  
}

//Irrelevant for this
void disabled() {}

//Used for choosing autonomous routines
void competition_initialize() {
   //Calls UI function for robot
   ui();
}

//Runs autonomous based on selection
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); 
  
  

  //Chooses examples as tests for the autonomous (replace these with appropiate autonomous stuff)
  switch (auton_selector) {
    case 1:
      chassis.set_drive_pid(10, 43, true);
      master.print(0, 0, "%d", auton_selector);
      break;
    case 2:
       master.print(0, 0, "%d", auton_selector);
       break;
    case 3:
         master.print(0, 0, "%d", auton_selector);
         drive_and_turn();
         break;
    case 4:
        master.print(0, 0, "%d", auton_selector);
        drive_example();
        break;
  }
}

//Numerous controls for the robot
void controls() {
  
  //Wings
  if(master.get_digital_new_press(DIGITAL_L2) || master.get_digital_new_press(DIGITAL_A)) {
    wings.toggle();
  }
  
  //Moves the intake
  if(master.get_digital(DIGITAL_R1)) {
    intake.move_voltage(12000);
  } else if(master.get_digital(DIGITAL_R2)) {
    intake.move_voltage(-12000);
  } else {
    intake.brake();
  }
  
  //Moves the cata at full speed (will change this)
  if(master.get_digital(DIGITAL_L1)) {
    kicker.move_voltage(12000);
  } 
  else {
    kicker.move_voltage(0);
  }
}

//Runs driver control.  With no field switch connected, this is the default one
void opcontrol() {
  Gif gif("/usd/fish.gif", lv_scr_act());
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  
  while(true) {
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    controls();

    pros::delay(util::DELAY_TIME);
  }
}
