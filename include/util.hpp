#ifndef UTIL_HPP
#define UTIL_HPP

#include "pros\motors.hpp"

namespace sdss_robotics_c {
    bool IsReversed(int num) {
        if(num > 0) {
            return false;
        }
        return true;
    }

    pros::MotorGear ConvertGearset(int gearset) {
        if(gearset == 36) {
            return pros::MotorGear::red;
        } else if(gearset == 18) {
            return pros::MotorGear::green;
        } else {
            return pros::MotorGear::blue;
        }
    }
}

#endif