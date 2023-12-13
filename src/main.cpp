#include "main.h"
#include "definitions.hpp"

void controls();

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  default_constants(); // Set the drive to your own constants from autons.cpp!
  chassis.set_joystick_threshold(3);

  chassis.initialize();

  cata.set_brake_mode(MOTOR_BRAKE_COAST);
  intake.set_brake_mode(MOTOR_BRAKE_COAST);
  rotationSensor.set_data_rate(5);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  ez::as::auton_selector.add_autons({
    Auton("Offensive Zone Qualifier", offensiveZoneQual),
    Auton("Offensive Zone Elimination", offensiveZoneElim),
    Auton("Defensive Zone Elimination", defensiveZone)
  });
  as::initialize();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  
  while(true) {
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    controls();

    pros::delay(util::DELAY_TIME);
  }
}

//Numerous controls for the robot
void controls() {
  //R1 = Intake in; L1 = Intake out; L2 = Catapult
  //For the wingsd

  static bool wingsState{ false };
  static bool intakeExtenderState{ false };

  if(master.get_digital_new_press(DIGITAL_A)) {
    wings.set_value(!wingsState);
    wingsState = !wingsState;
  }

  if(master.get_digital_new_press(DIGITAL_Y)) {
    intakeExtender.set_value(!intakeExtenderState);
    intakeExtenderState = !intakeExtenderState;
  }

  if(master.get_digital(DIGITAL_R1)) {
    intake.move_voltage(-12000);
  } else if(master.get_digital(DIGITAL_R2)) {
    intake.move_voltage(12000);
  } else {
    intake.brake();
  }

  static bool cataFlag{ false };

  if(master.get_digital(DIGITAL_L1)) {
    cata.move_voltage(12000);
  }

  if(rotationSensor.get_angle() < cataUpAngle) {
    cataFlag = false;
  }

  if(rotationSensor.get_angle() >= cataDownAngle && !cataFlag) {
    cata.brake();
    cataFlag = true;
  }
}
