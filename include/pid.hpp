#ifndef PID_HPP
#define PID_HPP

namespace pid {
    class Pid {
        public:

        //Value that we are getting from different operations (i.e. speed, degress of rotation, etc.)
        double real_value;

        //Testing, testing
        Pid(double setPoint, double proportional_gain);

        //Testing out proportional first
        void proportional();

        private:
        //pv = process value
        double pv;
        double error;
        //sp = setpoint
        double sp;
        //kp = proportional gain
        double kp;
        //P = proportional
        double P;
        

    };
}

#endif