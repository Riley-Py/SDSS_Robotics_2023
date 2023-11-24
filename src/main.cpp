#include "main.h"

Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)

  {15, -16, -17}

  // Right Chassis Ports (negative port will reverse it!)

  ,{-18, 19, 20}

  // IMU Port
  ,9  //Decide on this later on

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,2.5

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.666

);

adi::Pneumatics wings('A', false, false);
adi:: Pneumatics intake_extender ('B', false, false);
Motor intake(6, MotorGears::blue, MotorUnits::degrees);
Rotation rot_sen(4);
Motor cata(12, MotorGears::red, MotorUnits::degrees);





/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

  cata.set_brake_mode(MOTOR_BRAKE_COAST);

  rot_sen.reset_position();


	
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
void autonomous() {}

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
	

	while (true) {
		 chassis.move_drive((std::clamp(static_cast <int> (master.get_analog(ANALOG_LEFT_Y)), -100, 100)), std::clamp(static_cast <int> (master.get_analog(ANALOG_RIGHT_X)), -100, 100), 3, 3, chassis.left_motors, chassis.right_motors);
     double cataPosition = (rot_sen.get_position() / 100 );

      //R1 = Intake in; L1 = Intake out; L2 = Catapult
      //For the wings
      if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
          wings.toggle();
      }
      if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) {
        intake_extender.toggle();

      }
      if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
        intake.move_voltage(12000);


      }
      else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
        intake.move_voltage(-12000);
      }
      else {
        intake.brake();
      }

      if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
        cata.move_voltage(12000);
      }
      else {
        cata.brake();
      }
		 pros::delay(20);
     
     // Run for 20 ms then update

	}
}