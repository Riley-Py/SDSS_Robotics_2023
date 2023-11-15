#include "drive.hpp"

using namespace sdss_robotics_c;
//Declaration of the drive class
Drive::Drive(std::vector <int> leftMotorPorts, std::vector <int> rightMotorPorts, pros::MotorGears gearset, pros::MotorBrake brakeMode) {
    //Sets all of the ports to a motor and puts them to a list to get referenced later on
    for(int port : leftMotorPorts) {
        pros::Motor motor(port, gearset, pros::MotorUnits::degrees);
        motor.set_brake_mode(brakeMode);
        leftMotors.push_back(motor);
    }
    //Same as above, but for the right motors
    for(int port : rightMotorPorts) {
        pros::Motor motor(port, gearset, pros::MotorUnits::degrees);
        motor.set_brake_mode(brakeMode);
        rightMotors.push_back(motor);
    }
}

//Look in drive.hpp for comments
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