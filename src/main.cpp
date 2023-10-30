#include "main.h"
#include "definitions.hpp"
#include "pid.hpp" 

void initialize() {
  cata.set_brake_mode(MOTOR_BRAKE_COAST);

  cataRotationSensor.reset_position();
}
PID_1 pid_example;


void disabled() {}

void competition_initialize() {
  pid_example.sp = 65;
  pid_example.kp = 15;
  
  inertial.set_heading(0);

  pros::lcd::initialize();
  pros::lcd::set_text(1, "Testing");
  pros::lcd::set_background_color(150, 140, 140);

  while (true) {
    auton = pros::lcd::read_buttons();
    if (auton != 0) {
      break;
    }
    pros::delay(20);
    
  }
  pros::lcd::shutdown();






}

void autonomous() {
  if (auton == 1) {
    while (true) {
       inertial.set_rotation(90);
       master.set_text(0, 0, std::to_string(inertial.get_rotation()));

    }      
  }


  
}

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
      drivetrain.MoveMillivolts(forwardMillivolts, turnMillivolts);
    } else {
      drivetrain.Brake();
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
      flywheelA.move_voltage(12000);
      flywheelB.move_voltage(12000);
    } else {
      flywheelA.brake();
      flywheelB.brake();
    }

    if(master.get_digital(DIGITAL_L2)) {
      intake.move_voltage(12000);
    } else {
      intake.brake();
    }

    delay(20);
  }
}
