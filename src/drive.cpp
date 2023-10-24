#include "drive.hpp"
#include "util.hpp"

#include <cmath>

using namespace sdss_robotics_c;

Drive::Drive(std::vector <int> leftMotorPorts, std::vector <int> rightMotorPorts, int gearset) {
    for(int port : leftMotorPorts) {
        pros::Motor motor(std::abs(port), ConvertGearset(gearset), IsReverse(port));
        leftMotors.push_back(motor);
    }

    for(int port : rightMotorPorts) {
        pros::Motor motor(std::abs(port), ConvertGearset(gearset), IsReverse(port));
        rightMotors.push_back(motor);
    }
}