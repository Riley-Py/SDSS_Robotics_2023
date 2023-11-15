#include "main.h"
#include "definitions.hpp"

void initialize() {
  cata.set_brake_mode(MOTOR_BRAKE_COAST);

  cataRotationSensor.reset_position();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

//Curving of the joystick
int curveJoystick(const int input, const double t) {
  return (std::exp(-t / 10) + std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) * input;
}

void opcontrol() {
  while(true) {

    //Curve variables
    constexpr int turningCurve{ 3 };
    constexpr int forwardCurve{ 3 };


    //Values for the turning based on what the curveJoystick function spits out
    double turnVal{curveJoystick(std::clamp(static_cast<int>(master.get_analog(ANALOG_RIGHT_X)), -100, 100), turningCurve)};
    double forwardVal{curveJoystick(std::clamp(static_cast<int>(master.get_analog(ANALOG_LEFT_Y)), -100, 100), forwardCurve)};

    //The turn and forwaqrd millivolts are dependent on the curve
    double turnMillivolts{ turnVal * 96 };
    double forwardMillivolts{ forwardVal * 120 };

    //No stick drifting
    constexpr int deadband{ 3 };

    //If the joystick is moved beyond the deadband, move it forward or else it doesn't move
    if(std::abs(master.get_analog(ANALOG_LEFT_Y)) > deadband || std::abs(master.get_analog(ANALOG_RIGHT_X)) > deadband) {
      drivetrain.MoveMillivolts(forwardMillivolts, turnMillivolts);
    } else {
      drivetrain.Brake();
    }

    int cataPos{ cataRotationSensor.get_position() / 100 };

    //Debugging for the catapult 
    master.set_text(0, 0, std::to_string(cataPos));

    //Moves the catapult if R1 is pressed
    if(master.get_digital(DIGITAL_R1)) {
      if(cataPos >= 54 && cataPos <= 56) {
        cata.set_zero_position(cata.get_position());
        cata.move_absolute(360, 100);
      } else {
        cata.move_voltage(12000);
      }
    }

    static bool cataFlag{ false };

    //If the catapult's position is between 54-55 and the flag for the catapult that is down is false, stop it and make the flag true.s
    if(cataPos >= 54 && cataPos <= 55 && !cataFlag) {
      cata.brake();
      cataFlag = true;
    }    

    //If L1 is pressed, intake goes forward. If L2, then go backwards.  Otherwise, stop it

    if(master.get_digital(DIGITAL_L1)) {
      intake.move_voltage(12000);
    } else if(master.get_digital(DIGITAL_L2)) {
      intake.move_voltage(-12000);
    } else {
      intake.brake();
    }

    delay(20);
  }
}
