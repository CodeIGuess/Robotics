// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         11              
// front_left           motor         20              
// back_left            motor         10              
// back_right           motor         1               
// Controller1          controller                    
// left_intake          motor         19              
// right_intake         motor         12              
// arm_right            motor         5               
// arm_left             motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\efrag                                            */
/*    Created:      Thu Oct 03 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "robot-config.h"
#include "frame-class.h"

using namespace vex;

competition Competition;

// Base Variables
int speedBase = 60;
int speed = speedBase;

// Distance Variables
float rotations = 360;
double first_tile = rotations*2.08;  //THIS MEASUREMENT IS NOT SET
double one_tile = rotations*2.32; //THIS MEASUREMENT IS NOT SET

// Base Movement
void basevelocity(double n) {
  front_left.setVelocity(n, percent);
  front_right.setVelocity(n, percent);
  back_right.setVelocity(n, percent);
  back_left.setVelocity(n, percent);
}
void GO(double n) {
  front_right.rotateFor(n, turns, false);
  back_right.rotateFor(n, turns, false);
  front_left.rotateFor(n, turns, false);
  back_left.rotateFor(n, turns);
}
void turnfor(double n) {
  front_right.spinFor(n, degrees, false);
  back_right.spinFor(n, degrees, false);
  front_left.spinFor(-n, degrees, false);
  back_left.spinFor(-n, degrees);
}

// Distance Movement
void move_firsttile(double t) {
  front_right.rotateFor(first_tile*t, deg, false);
  back_right.rotateFor(first_tile*t, deg, false);
  front_left.rotateFor(first_tile*t, deg, false);
  back_left.rotateFor(first_tile*t, deg);
}
void move_onetile(double t) {
  front_right.rotateFor(one_tile*t, deg, false);
  back_right.rotateFor(one_tile*t, deg, false);
  front_left.rotateFor(one_tile*t, deg, false);
  back_left.rotateFor(one_tile*t, deg);
}
void move_onetiletime(double t) { // Uses millisecond
  front_right.spin(forward);
  back_right.spin(forward);
  front_left.spin(forward);
  back_left.spin(forward);

  vex::task::sleep(t);

  front_right.stop();
  back_right.stop();
  front_left.stop();
  back_left.stop();
}

// Ramp Movement
void rampUp() {
  ramp.spin(forward);
}
void rampDown() {
  ramp.spin(reverse);
}
void rampStop() {
  ramp.setVelocity(0, percent);
  ramp.spin(forward);
}

// Arms Movement
void up() {
  arms.setVelocity(100,percent);
  arms.spin(forward);
}
void down() {
  arms.setVelocity(50,percent);
  arms.spin(reverse);
}

// Intake Movement
void intake() {
  left_intake.spin(forward);
  right_intake.spin(forward);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("IN");
}
void outtake() {
  left_intake.spin(reverse);
  right_intake.spin(reverse);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("OT");
}
void stoptake() {
  left_intake.setVelocity(0, percent);
  right_intake.setVelocity(0, percent);
  left_intake.spin(forward);
  right_intake.spin(forward);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("NE");
}

void pre_auton() {
  
}

void autonomous() {
  
}

void usercontrol() {
  while (1) {
    
    float Axis1 = -Controller1.Axis1.value();
    float Axis2 = -Controller1.Axis2.value();
    float Axis3 =  Controller1.Axis3.value();
    float Axis4 = -Controller1.Axis4.value();

    front_left.setVelocity(speed, percent);
    back_right.setVelocity(speed, percent);
    back_left.setVelocity(speed, percent);
    front_right.setVelocity(speed, percent);


    front_left.spin(directionType::fwd, Axis3 - Axis4, velocityUnits::pct);
    back_left.spin(directionType::fwd, Axis3 - Axis4, velocityUnits::pct);

    front_right.spin(directionType::fwd, Axis3 + Axis4, velocityUnits::pct);
    back_right.spin(directionType::fwd, Axis3 + Axis4, velocityUnits::pct);
    
    // Arms
    if(Controller1.ButtonL1.pressing()) {up();}
    else if (Controller1.ButtonL2.pressing()) {down();}
    else {arms.stop();}
    
    // Intake Velocity
    left_intake.setVelocity(100, percent);
    right_intake.setVelocity(100, percent);
    if(Controller1.ButtonR2.pressing()) {outtake();}
    else if (Controller1.ButtonR1.pressing()) {intake();}
    else {stoptake();}

    // Ramp Velocity
    ramp.setVelocity(70, percent);
    if(Controller1.ButtonDown.pressing()){rampUp();}
    else if(Controller1.ButtonUp.pressing()){rampDown();}
    else{rampStop();}

    if(Controller1.ButtonA.pressing()){
      ramp.spin(directionType::fwd, Axis2, velocityUnits::pct);
    }


    if (Controller1.ButtonB.pressing()) {
      Controller1.Screen.clearLine();
      Controller1.Screen.print(round(Potentiometer.angle(degrees)*1.005)-1);
    }
    if (Controller1.ButtonA.pressing()) {
      speed = 100;
    } else {
      speed = speedBase;
    }

    task::sleep(20);
  }
}

int main() {

    vexcodeInit();

    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}