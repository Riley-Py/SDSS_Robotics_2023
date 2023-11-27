#include "main.h"
#include "definitions.hpp"

void initialize() {
  cata.set_brake_mode(MOTOR_BRAKE_HOLD);

  cataRotationSensor.reset_position();
  cataRotationSensor.set_data_rate(5);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

int curveJoystick(const int input, const int t) {
  return (std::exp(-t / 10) + std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) * input;
}

void opcontrol() {
  while(true) {
    constexpr int turningCurve{ 3 };
    constexpr int forwardCurve{ 3 };

    int turnVal{curveJoystick(std::clamp(static_cast<int>(master.get_analog(ANALOG_RIGHT_X)), -100, 100), turningCurve)};
    int forwardVal{curveJoystick(std::clamp(static_cast<int>(master.get_analog(ANALOG_LEFT_Y)), -100, 100), forwardCurve)};

    int turnMillivolts{ turnVal * 96 };
    int forwardMillivolts{ forwardVal * 120 };

    constexpr int deadband{ 3 };

    if(std::abs(master.get_analog(ANALOG_LEFT_Y)) > deadband || std::abs(master.get_analog(ANALOG_RIGHT_X)) > deadband) {
      drivetrain.MoveMillivolts(forwardMillivolts, turnMillivolts);
    } else {
      drivetrain.Brake();
    }

    master.set_text(0, 0, std::to_string(cataRotationSensor.get_position()));

    static bool cataFlag{ false };

    if(master.get_digital(DIGITAL_L2)) {
      cata.move_voltage(12000);
    }

    if(cataRotationSensor.get_position() < 5900) {
      cataFlag = false;
    }

    if(cataRotationSensor.get_position() >= 5900 && !cataFlag) {
      cata.brake();
      cataFlag = true;
    }

    if(master.get_digital(DIGITAL_R1)) {
      intake.move_voltage(12000);
    } else if(master.get_digital(DIGITAL_L1)) {
      intake.move_voltage(-12000);
    } else {
      intake.brake();
    }

    delay(20);
  }
}
