#ifndef DRIVE_HPP
#define DRIVE_HPP

#include "pros\motors.hpp"


#include <list>

namespace sdss_robotics_c {
    class Drive {
        public:
        Drive(std::list<int> leftMotorPorts, std::list<int> rightMotorPorts, pros::motor_gearset_e_t Gearset, pros::motor_brake_mode_e_t brakeMode);

        void MoveMillivolts(int forwardMillivolts, int turnMillivolts);
        void Brake();
        
        private:
        std::vector <pros::Motor> leftMotors;
        std::vector <pros::Motor> rightMotors;
    };
}

#endif