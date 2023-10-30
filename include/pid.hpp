#ifndef PID_HPP
#define PID_HPP


 class PID_1 {
        public:
            double sp; //Setpoint/goal for PID
            double kp; // Proportional gain 
        private:
            double error = 0;
            double P = 0; // Proportional portion
        int Proportional (double PV)  {//Process value (insert values into this)
            error = sp - PV;
            P = kp * error;
            
            if (error != 0) {
                Proportional(P);
            }
            else {
                return 0;
            }
            return P;
      
        }
    };

#endif