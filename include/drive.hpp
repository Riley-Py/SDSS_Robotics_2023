#ifndef DRIVE_HPP
#define DRIVE_HPP

#include "pros\motors.hpp"
#include <vector>

namespace sdss_robotics_c {
    class Drive {
        public:
        Drive(std::vector <int> leftMotorPorts, std::vector <int> rightMotorPorts, pros::MotorGears gearset, pros::MotorBrake brakeMode);

        void MoveMillivolts(int forwardMillivolts, int turnMillivolts);
        void Brake();
        
        private:
        std::vector <pros::Motor> leftMotors;
        std::vector <pros::Motor> rightMotors;
    };
}

#endif