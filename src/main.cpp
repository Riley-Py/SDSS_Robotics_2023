#include "main.h"
#include "definitions.h"

void initialize() {
  rightMotors.set_brake_modes(E_MOTOR_BRAKE_COAST);
  leftMotors.set_brake_modes(E_MOTOR_BRAKE_COAST);

  leftTop.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightTop.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

int curveJoystick(const int input, const double t) {
  return (std::exp(-t / 10) + std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) * input;
}

void opcontrol() {
  while(true) {
    constexpr int turningCurve{ 3 };
    constexpr int forwardCurve{ 3 };

    double turnVal{curveJoystick(std::clamp(static_cast<int>(master.get_analog(ANALOG_RIGHT_X)), -100, 100), turningCurve)};
    double forwardVal{curveJoystick(std::clamp(static_cast<int>(master.get_analog(ANALOG_LEFT_Y)), -100, 100), forwardCurve)};

    double turnMillivolts{ turnVal * 96 };
    double forwardMillivolts{ forwardVal * 120 };

    constexpr int deadband{ 3 };

    if(std::abs(master.get_analog(ANALOG_LEFT_Y)) > deadband || std::abs(master.get_analog(ANALOG_RIGHT_X)) > deadband) {
      rightMotors.move_voltage(forwardMillivolts - turnMillivolts);
      rightTop.move_voltage(forwardMillivolts - turnMillivolts);

      leftMotors.move_voltage(forwardMillivolts + turnMillivolts);
      leftTop.move_voltage(forwardMillivolts + turnMillivolts);
    } else {
      rightMotors.move_voltage(0);
      rightTop.move_voltage(0);

      leftMotors.move_voltage(0);
      leftTop.move_voltage(0);
    }
    static bool aPressed{ false };
    static bool cataDown{ false };

    static bool limitReached{ false };

    if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      if(cataDown) {
        cata.move(100);
        cataDown = false;
        limitReached = true;
      } else {
        cata.move(100);
        aPressed = true;
      }
    }

    if(cataLimit.get_value() && aPressed && !limitReached)  {
      cata.move(0);
      cataDown = true;
      aPressed = false;
    }

    if(!cataLimit.get_value()) {
      limitReached = false;
    }

    if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      aaa.move(127);
      bbb.move(127);
    } else {
      aaa.move(0);
      bbb.move(0);
    }

    delay(20);
  }
}
