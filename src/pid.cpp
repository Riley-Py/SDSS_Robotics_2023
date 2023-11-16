#include "pid.hpp"

pid::Pid::Pid(double setPoint, double proportional_gain) {
    kp = setPoint;
    sp = proportional_gain;
}

double pid::Pid::proportional(double real_value) {
    error = sp - real_value;
    P = kp * error;

    if (error == 0) {
        return 0;
    }

     
    
    return P; 
}

