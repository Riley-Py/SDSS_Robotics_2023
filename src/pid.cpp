#include "pid.hpp"

pid::Pid::Pid(double setPoint, double proportional_gain) {
    kp = setPoint;
    sp = proportional_gain;
}

void pid::Pid::proportional() {
    error = sp - real_value;
    P = kp * error;

    if (P != 0) {
        proportional();
    }    
}

