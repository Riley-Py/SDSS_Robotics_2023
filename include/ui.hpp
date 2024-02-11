#ifndef UI_HPP
#define UI_HPP

#include "main.h"

extern const char * btn_names[8];
extern lv_res_t callback(lv_obj_t * btnmatrix, const char* name);
extern void ui();

extern string autonSelected;

#endif