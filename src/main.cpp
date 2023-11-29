#include "main.h"
#include "definitions.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(3, 3); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // Initialize chassis
  chassis.initialize();

  intake.set_brake_mode(MOTOR_BRAKE_COAST);
  cata.set_brake_mode(MOTOR_BRAKE_COAST);
  cataRotationSensor.set_position(0);
  cataRotationSensor.set_data_rate(5);
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
void competition_initialize() {}

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

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
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

    master.set_text(0, 0, std::to_string(cataRotationSensor.get_angle()));

    static bool cataFlag{ false };

    if(master.get_digital(DIGITAL_L2)) {
      cata.move_voltage(10000);
    }

    if(cataRotationSensor.get_position() < 6000) {
      cataFlag = false;
    }

    if(cataRotationSensor.get_position() >= 6000 && !cataFlag) {
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

    if(master.get_digital_new_press(DIGITAL_A)) {
      wings.toggle();
    }
    
    if(master.get_digital_new_press(DIGITAL_Y)) {
      intakeExtender.toggle();
    }

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
