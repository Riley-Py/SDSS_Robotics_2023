#include "main.h"
#include "definitions.hpp"

void display() {
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}

void initialize() {
  leftMotors.set_brake_modes(MOTOR_BRAKE_COAST);
  rightMotors.set_brake_modes(MOTOR_BRAKE_COAST);

  cata.set_brake_mode(MOTOR_BRAKE_COAST);

  cataRotationSensor.reset_position();

  pros::lcd::initialize();
  chassis.calibrate();
  pros::Task screenTask(display);
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
      leftMotors.move_voltage(forwardMillivolts + turnMillivolts);
      rightMotors.move_voltage(forwardMillivolts - turnMillivolts);
    } else {
      leftMotors.brake();
      rightMotors.brake();
    }

    int cataPos{ cataRotationSensor.get_position() / 100 };

    master.set_text(0, 0, std::to_string(cataPos));
    
    if(master.get_digital(DIGITAL_R1)) {
      if(cataPos >= 54 && cataPos <= 56) {
        cata.set_zero_position(cata.get_position());
        cata.move_absolute(360, 100);
      } else {
        cata.move_voltage(12000);
      }
    }

    static bool cataFlag{ false };

    if(cataPos >= 54 && cataPos <= 55 && !cataFlag) {
      cata.brake();
      cataFlag = true;
    }    

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
