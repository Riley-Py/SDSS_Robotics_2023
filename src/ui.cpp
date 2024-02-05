#include "main.h"
#include "definitions.hpp"

static const char * btn_names[] = {"Autonomous (Defensive)", "Autonomous (Offensive)", "\n","Skills", "Elimination", ""};


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