#include "ui.hpp"

//Names for buttons on button matrix (DO NOT REMOVE EMPTY SPACE AT THE END)
const char * btn_names[] = {"Autonomous (Defensive)", "Autonomous (Offensive)", "\n","Elimination (Offensive)", "Elimination (Defensive)", ""};

//Gets the autonomous selected from the autonomous selector
string autonSelected;

//The function that is called whenever a button is pressed
lv_res_t callback(lv_obj_t * btnmatrix, const char* name) {
  master.set_text(0, 0, name);
  autonSelected = name;
  return LV_RES_OK;
}

//The UI itself
void ui() {

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