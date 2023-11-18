#ifndef NEW_DRIVE_HPP
#define NEW_DRIVE_HPP

#include "pros/motor_group.hpp"
#include <vector>
#include <iostream>
#include <array>

class Drive {
    public:
    //Drive class for the left motors, the right motors, and the gearing (i.e. if they are red cartridges or blue cartridges)
    Drive(std::vector<std::int8_t> leftmotors, std::vector<std::int8_t> rightmotors, pros::MotorGear gearing);

    //Moves the drivetrain by a certain amount of millivolts
    void movemillivolts(double movemillivolts, double turnmillivolts);
    
    //Brakes the motors
    void brake(); 


    
   

    
    

    

    

     


};


#endif