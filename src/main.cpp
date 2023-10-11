#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor rightA(19, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightB(20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group rightMotors({rightA, rightB});

pros::Motor leftA(19, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftB(20, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
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

constexpr int turningCurve{ 6 };
constexpr int turningRed{ false };

constexpr int forwardCurve{ 6 };
constexpr int forwardRed{ false };

int curveJoystick(const bool red, const int input, const double t) {
  if(red) {
    return (std::exp(-t/10) + std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) * input;
  } else {
    return std::exp(((std::abs(input) - 100) * t) / 1000) * input;
  }
}

void opcontrol() {
    constexpr int deadband{ 3 };

    while(true) {
        double turnVal{ curveJoystick(false, master.get_analog(ANALOG_RIGHT_X), turningCurve) };
        double forwardVal{ curveJoystick(false, master.get_analog(ANALOG_LEFT_Y), forwardCurve) };

        double turnVolts{ turnVal * 0.12 };
        double forwardVolts{ forwardVal * 0.12 };

        if(master.get_analog(ANALOG_LEFT_Y) > deadband || master.get_analog(ANALOG_RIGHT_X)) {
            rightMotors.move_voltage(forwardVolts - turnVolts);
            rightTop.move_voltage(forwardVolts - turnVolts);

            leftMotors.move_voltage(forwardVolts + turnVolts);
            leftTop.move_voltage(forwardVolts + turnVolts);
        } else {
            rightMotors.move_voltage(0);
            leftMotors.move_voltage(0);
            rightTop.move_voltage(0);
            leftTop.move_voltage(0);
        }
    }
}
