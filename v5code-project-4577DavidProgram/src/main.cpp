/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*------------------Important Lines-------------------*/
/*              Pre-Auton     Line: 47                */
/*                  Auton     Line: 64                */
/*         Driver Control     Line: 80                */
/*----------------------------------------------------*/


#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

// A global instance of competition
competition Competition;
vex::motor FrontRight(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor FrontLeft(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::motor RearRight(vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor RearLeft(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::controller Controller1(vex::controllerType::primary);
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
int StrafeSpeed = 1;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  FrontLeft.setBrake(vex::brakeType::coast);
  RearLeft.setBrake(vex::brakeType::coast);
  FrontRight.setBrake(vex::brakeType::coast);
  RearRight.setBrake(vex::brakeType::coast);
  while (1) {
    //All D.C code goes into r1 loop (R1 = Deadman Switch in case of controller malfunction)
    if (Controller1.ButtonR1.pressing()) {
      //Tank control with sticks until modifier pressed
      //modifier should be r2, r2 disables sticks and enable 4 way cardinal movemement
        RearLeft.setVelocity(Controller1.Axis3.position(), vex::percentUnits::pct);
        FrontLeft.setVelocity(Controller1.Axis3.position(), vex::percentUnits::pct);
        RearRight.setVelocity(Controller1.Axis2.position(), vex::percentUnits::pct);
        FrontRight.setVelocity(Controller1.Axis2.position(), vex::percentUnits::pct);
        FrontLeft.spin(forward);
        RearLeft.spin(forward);
        FrontRight.spin(forward);
        RearRight.spin(forward);
        if(Controller1.ButtonR1.pressing() & Controller1.ButtonR2.pressing()) {
          if(Controller1.ButtonUp.pressing()) {
            FrontLeft.spin(forward, StrafeSpeed, vex::percentUnits::pct);
            FrontRight.spin(forward, StrafeSpeed, vex::percentUnits::pct);
            RearRight.spin(forward, StrafeSpeed, vex::percentUnits::pct);
            RearLeft.spin(forward, StrafeSpeed, vex::percentUnits::pct);
          } else if(Controller1.ButtonDown.pressing()) {
            FrontLeft.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
            FrontRight.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
            RearRight.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
            RearLeft.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
          } else if(Controller1.ButtonRight.pressing()) {
            FrontLeft.spin(forward, StrafeSpeed, vex::percentUnits::pct);
            FrontRight.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
            RearRight.spin(forward, StrafeSpeed, vex::percentUnits::pct);
            RearLeft.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
          } else if(Controller1.ButtonLeft.pressing()) {
            FrontLeft.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
            FrontRight.spin(forward, StrafeSpeed, vex::percentUnits::pct);
            RearRight.spin(reverse, StrafeSpeed, vex::percentUnits::pct);
            RearLeft.spin(forward, StrafeSpeed, vex::percentUnits::pct);
          }
        }
      } else {
  FrontLeft.stop();
  FrontRight.stop();
  RearRight.stop();
  RearLeft.stop();

    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
