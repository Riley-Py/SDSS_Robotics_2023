#include "new_drive.hpp"
#include <cmath>


Drive::Drive(std::vector<std::int8_t> leftmotors, std::vector<std::int8_t> rightmotors, pros::MotorGear gearing) {
    pros::MotorGroup left(leftmotors, gearing);
    pros::MotorGroup right(rightmotors, gearing);

    


    


}

void Drive::movemillivolts(double movemillivolts, double turnmillivolts) {
    
}








