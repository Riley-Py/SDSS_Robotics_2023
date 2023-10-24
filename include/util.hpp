#ifndef UTIL_HPP
#define UTIL_HPP

#include "pros\motors.hpp"

namespace sdss_robotics_c {
    bool IsReverse(int num) {
        if(num > 0) {
            return false;
        }
        return true;
    }

    pros::motor_gearset_e_t ConvertGearset(int gearset) {
        if(gearset == 36) {
            return pros::E_MOTOR_GEAR_RED;
        } else if(gearset == 18) {
            return pros::E_MOTOR_GEAR_GREEN;
        } else {
            return pros::E_MOTOR_GEAR_BLUE;
        }
    }
}

#endif