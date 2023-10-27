#ifndef PID_HPP
#define PID_HPP

namespace pidd {
    class PID {
        public:
            double sp; //Setpoint/goal for PID
            double kp; // Proportional gain 
        private:
            double error = 0;
            double P = 0; //P value for proportional portion
        int Proportional (double PV)  { //Process value
            error = sp - PV;
            P = kp * error;

            if (error == 0){
                return 0;
            }
            else {
                return P;
            }
        }
    };
}

#endif