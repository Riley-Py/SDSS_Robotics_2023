#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor rightA(19, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightB(20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group rightMotors({rightA, rightB});

pros::Motor leftA(16, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftB(17, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group leftMotors({leftA, leftB});

pros::Motor leftTop(15, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightTop(18, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

void initialize() {
    rightMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    leftMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

constexpr int turningCurve{ 3 };

constexpr int forwardCurve{ 3 };

int curveJoystick(const bool red, const int input, const double t) {
  if(red) {
    return (std::exp(-t / 10) + std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) * input;
  } else {
    return std::exp(((std::abs(input) - 100) * t) / 1000) * input;
  }
}

void opcontrol() {
    constexpr int deadband{ 3 };

    while(true) {
      double turnVal{ curveJoystick(false, std::clamp(static_cast<int>(master.get_analog(ANALOG_RIGHT_X)), -100, 100), turningCurve) };
      double forwardVal{ curveJoystick(false, std::clamp(static_cast<int>(master.get_analog(ANALOG_LEFT_Y)), -100, 100), forwardCurve) };

      double turnMillivolts{ turnVal * 96 };
      double forwardMillivolts{ forwardVal * 120 };

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
      
      pros::delay(20);
    }
}
