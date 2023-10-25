#include "drive.hpp"
#include "util.hpp"

#include <cmath>

using namespace sdss_robotics_c;

Drive::Drive(std::vector <int> leftMotorPorts, std::vector <int> rightMotorPorts, pros::motor_gearset_e_t gearset, pros::motor_brake_mode_e_t brakeMode) {
    for(int port : leftMotorPorts) {
        pros::Motor motor(std::abs(port), ConvertGearset(gearset), IsReversed(port));
        motor.set_brake_mode(brakeMode);
        leftMotors.push_back(motor);
    }

    for(int port : rightMotorPorts) {
        pros::Motor motor(std::abs(port), ConvertGearset(gearset), IsReversed(port));
        motor.set_brake_mode(brakeMode);
        rightMotors.push_back(motor);
    }
}

void Drive::MoveMillivolts(int forwardMillivolts, int turnMillivolts) {
    for(pros::Motor motor : rightMotors) {
        motor.move_voltage(forwardMillivolts - turnMillivolts);
    }
    for(pros::Motor motor : leftMotors) {
        motor.move_voltage(forwardMillivolts + turnMillivolts);
    }
}

void Drive::Brake() {
    for(pros::Motor motor : rightMotors) {
        motor.brake();
    }
    for(pros::Motor motor : leftMotors) {
        motor.brake();
    }
}