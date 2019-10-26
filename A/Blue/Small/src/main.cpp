// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         1               
// front_left           motor         8               
// back_left            motor         9               
// back_right           motor         2               
// Controller1          controller                    
// left_intake          motor         3               
// right_intake         motor         7               
// arms                 motor         14              
// Vision               vision        13              
// Potentiometer        pot           A               
// Ultrasonic           sonar         C, D            
// ramp                 motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         1               
// front_left           motor         8               
// back_left            motor         9               
// back_right           motor         2               
// Controller1          controller                    
// left_intake          motor         3               
// right_intake         motor         7               
// arms                 motor         14              
// Vision               vision        13              
// Potentiometer        pot           A               
// Ultrasonic           sonar         C, D            
// ramp                 motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         1               
// front_left           motor         8               
// back_left            motor         9               
// back_right           motor         2               
// Controller1          controller                    
// left_intake          motor         3               
// right_intake         motor         7               
// arms                 motor         14              
// Vision               vision        13              
// Potentiometer        pot           A               
// Ultrasonic           sonar         C, D            
// ramp                 motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
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
   
void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void rampUp(){
  ramp.spin(forward);
}
void rampDown(){
  ramp.spin(reverse);
}
void rampStop() {
  ramp.setVelocity(0, percent);
  ramp.spin(forward);
}

void turnFor(double n) {
  front_right.spinFor(n, degrees);
  back_right.spinFor(n, degrees);
  front_left.spinFor(-n, degrees);
  back_left.spinFor(-n, degrees);
}

void basevelocity(double n){
  front_left.setVelocity(n, percent);
  front_right.setVelocity(n, percent);
  back_right.setVelocity(n, percent);
  back_left.setVelocity(n, percent);
}

void goForward(double n) {
  front_right.spinFor(n, turns);
  back_right.spinFor(n, turns);
  front_left.spinFor(n, turns);
  back_left.spinFor(n, turns);
}

void up() {
  arms.setVelocity(50,percent);
  arms.spin(reverse);
}
void down(){
  arms.setVelocity(100,percent);
  arms.spin(forward);
}

void intake(){
  left_intake.spin(forward);
  right_intake.spin(forward);
}
void outtake(){
  left_intake.spin(reverse);
  right_intake.spin(reverse);
}
void stoptake() {
  left_intake.setVelocity(0, percent);
  right_intake.setVelocity(0, percent);
  left_intake.spin(forward);
  right_intake.spin(forward);
}

event checkPurple = event();

void hasPurpleCallback() {
	Brain.Screen.setFont(mono40);
	Brain.Screen.clearLine(1, purple);
	Brain.Screen.setCursor(Brain.Screen.row(), 1);
	Brain.Screen.setCursor(1, 1);
	Vision.takeSnapshot(Vision__PURPLE_CUBE);
	if(Vision.objectCount > 0) {
		Brain.Screen.print("CUBE CUBE CUBE PURPLE YES GOOD");
	} else {
		Brain.Screen.print("No cube");
	}
}

void autonomous( void ) {



}

void usercontrol( void ) {
  while (1) {

    intake();

    Brain.Screen.print("I AM WORKING YEEEEEEEEE!");
    
    float Axis1 = -Controller1.Axis1.value();
    float Axis2 = -Controller1.Axis2.value();
    float Axis3 =  Controller1.Axis3.value();
    float Axis4 = -Controller1.Axis4.value();

    double vel = 100 * (2/3);

    front_left.setVelocity(vel, percent);
    back_right.setVelocity(vel, percent);
    back_left.setVelocity(vel, percent);
    front_right.setVelocity(vel, percent);


    front_left.spin(directionType::fwd, Axis3 + Axis1, velocityUnits::pct);
    back_left.spin(directionType::fwd, Axis3 + Axis1, velocityUnits::pct);

    front_right.spin(directionType::fwd, Axis3 - Axis1, velocityUnits::pct);
    back_right.spin(directionType::fwd, Axis3 - Axis1, velocityUnits::pct);
    
    if(Controller1.ButtonL2.pressing()) {up();}
    else if (Controller1.ButtonL1.pressing()) {down();}
    else {arms.stop();}
    
    left_intake.setVelocity(100, percent);
    right_intake.setVelocity(100, percent);

    if(Controller1.ButtonR2.pressing()) {outtake();}
    else if (Controller1.ButtonR1.pressing()) {intake();}
    else {stoptake();}

    if(Controller1.ButtonB.pressing()){
      Controller1.Screen.clearLine();
      Controller1.Screen.print(round(Potentiometer.angle(degrees)*1.005)-1);
    }

    ramp.setVelocity(100, percent);
    if(Controller1.ButtonUp.pressing()){rampUp();}
    else if(Controller1.ButtonDown.pressing()){rampDown();}
    else{rampStop();}
    //ramp.spinFor(Axis2, degrees);

    //ramp.spinFor(Axis2, degrees);

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(Axis2);

    task::sleep(20);
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {

    vexcodeInit();

    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
       
}