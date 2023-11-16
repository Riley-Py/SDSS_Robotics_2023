#ifndef DRIVE_HPP
#define DRIVE_HPP

#include "pros\motors.hpp"
#include <vector>

namespace sdss_robotics_c {
    class Drive {
        public:
        //Drive class for the robot that includes ports for the left motors, ports for the right, the gearing, and the braking
        Drive(std::vector <int> leftMotorPorts, std::vector <int> rightMotorPorts, pros::MotorGears gearset, pros::MotorBrake brakeMode);

        //Moves the drivetrain a certain amount based on the amount millivolts
        void MoveMillivolts(int forwardMillivolts, int turnMillivolts);
        //Stops the drivetrain
        void Brake();

        //Gets the velocity of the motors using a numerical average
        double Get_Velocity();
        
        private:
        //Funky way to give the motors the attributes by putting them in a list
        std::vector <pros::Motor> leftMotors;
        std::vector <pros::Motor> rightMotors;
        //Stores an average of current velocity using the right motors (implement using left as well for turning)
        double current_velocity; 
    };
}

#endif