#include "main.h"

#include "kepler/control/chassis.h"
#include "kepler/control/rack.h"
#include "kepler/control/arm.h"

#include "kepler/util/odometry.h"
#include "kepler/util/misc.h"

#include "kepler/displayController.h"
#include "kepler/autonController.h"

void initialize() {
  macro::print("Starting Init Routine");

  Autonomous Auton;
  macro::print("Auton Set!");

  // Class Initialization
  Odometry odom;
  Chassis chassis;
  Rack rack;
  Arm arm;

  Display Disp;

  // Motor Initialization
  arm.tarePos();

  rack.setBrakeType(MOTOR_BRAKE_HOLD);
  arm.setBrakeType(MOTOR_BRAKE_HOLD);

  io::RollerL.set_brake_mode(MOTOR_BRAKE_HOLD);
	io::RollerR.set_brake_mode(MOTOR_BRAKE_HOLD);
  macro::print("Motors Initialized!");

  // Threads
  pros::Task odomController(odom.start, NULL, "Odometry Tracker");
  macro::print("Odometry Initialized!");

  pros::Task baseController(chassis.start, NULL, "Chassis Controller");
  macro::print("Chassis Initialized!");

  pros::Task rackController(rack.start, NULL, "Rack Controller");
  macro::print("Rack Initialized!");

  pros::Task armController(arm.start, NULL, "Arm Controller");
  macro::print("Arm Initialized!");

  pros::Task b_display(Disp.start, NULL, "Display Controller");
  b_display.set_priority(TASK_PRIORITY_MIN);
  macro::print("Display Initialized!");

  // Path Pathmaker;
  // pros::Task pathMaker(Pathmaker.start, NULL, "PathMaker");
  // pathMaker.set_priority(TASK_PRIORITY_MIN);
  // print("PathMaker Initialized!");

  std::cout << "Initialization Done!" << std::endl;
}

void disabled() { }

void competition_initialize() { }
