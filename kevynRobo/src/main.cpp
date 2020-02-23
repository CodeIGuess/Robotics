// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// backRight            motor         10              
// frontRight           motor         9               
// backLeft             motor         8               
// frontLeft            motor         7               
// ramp                 motor         2               
// arms                 motor         1               
// intakeLeft           motor         11              
// intakeRight          motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\efrag                                            */
/*    Created:      Thu Oct 03 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
Robot Length: ~20''
Tile Length:  ~23''
Rotation: ~15''
*/

#include "vex.h"
#include "robot-config.h"

using namespace vex;

competition Competition;

// Speed variables
int speedBase = 75;
int speed = speedBase;

// Distance variables
float rotations = 360;
double firstTile = 2.08 * rotations; //THIS MEASUREMENT IS NOT SET
double oneTile = 2.32 * rotations; //THIS MEASUREMENT IS NOT SET

// Screen functions

void print(double n) {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print(n);
}
void print(double n, double cursorX, double cursorY) {
  Controller1.Screen.setCursor(cursorY, cursorX);
  Controller1.Screen.print(n);
}
void print(char* n, double cursorX, double cursorY) {
  Controller1.Screen.setCursor(cursorY, cursorX);
  Controller1.Screen.print(n);
}
void printBrain(double n) {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(n);
}
void printBrain(double n, double cursorX, double cursorY) {
  Brain.Screen.setCursor(cursorY, cursorX);
  Brain.Screen.print(n);
}
void printBrain(char* n, double cursorX, double cursorY) {
  Brain.Screen.setCursor(cursorY, cursorX);
  Brain.Screen.print(n);
}

void clearScreen() {
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1, 1);
}

// Autonomous helper functions
void baseVelocity(double n) {
  speed = float(n) / 100;
}
void moveTurns(double n) {
  frontRight.rotateFor(n, turns, false);
  backRight.rotateFor(n, turns, false);
  frontLeft.rotateFor(n, turns, false);
  backLeft.rotateFor(n, turns);
}
void moveTurns(double nl, double nr) {
  frontRight.rotateFor(nr, turns, false);
  backRight.rotateFor(nr, turns, false);
  frontLeft.rotateFor(nl, turns, false);
  backLeft.rotateFor(nl, turns);
}
void moveDegrees(double n) {
  frontRight.spinFor(n, degrees, false);
  backRight.spinFor(n, degrees, false);
  frontLeft.spinFor(n, degrees, false);
  backLeft.spinFor(n, degrees);
}
void moveDegrees(double nl, double nr) {
  frontRight.spinFor(nr, degrees, false);
  backRight.spinFor(nr, degrees, false);
  frontLeft.spinFor(nl, degrees, false);
  backLeft.spinFor(nl, degrees);
}
void moveInches(double n) {
  frontRight.spinFor(n*25, degrees, false);
  backRight.spinFor(n*25, degrees, false);
  frontLeft.spinFor(n*25, degrees, false);
  backLeft.spinFor(n*25, degrees);
}
void moveInches(double n1, double n2) {
  frontRight.spinFor(n2*25, degrees, false);
  backRight.spinFor(n2*25, degrees, false);
  frontLeft.spinFor(n1*25, degrees, false);
  backLeft.spinFor(n1*25, degrees);
}

// Ramp movement
void rampUp(double t) {
  ramp.spin(forward);
  task::sleep(t);
}
void rampDown(double t) {
  ramp.spin(reverse);
  task::sleep(t);
}
void rampStop() {
  ramp.setVelocity(0, percent);
  ramp.spin(forward);
}

// Arm movement
void armsUp(double t) {
  arms.setVelocity(100, percent);
  arms.spin(forward);
  // For how long will it move
  vex::task::sleep(t);
}
void armsDown(double t) {
  arms.setVelocity(100, pct);
  arms.spin(reverse);
  // For how long will it move
  vex::task::sleep(t);
}

// Intake movement
void intake(double p) {
  intakeLeft.setVelocity(p * speed / 100, percent);
  intakeRight.setVelocity(p * speed / 100, percent);
  intakeLeft.spin(reverse);
  intakeRight.spin(reverse);
}
void outtake(double p) {
  intakeLeft.setVelocity(p * speed / 100, percent);
  intakeRight.setVelocity(p * speed / 100, percent);
  intakeLeft.spin(forward);
  intakeRight.spin(forward);
}
void stoptake() {
  intakeLeft.setVelocity(0, percent);
  intakeRight.setVelocity(0, percent);
  intakeLeft.spin(forward);
  intakeRight.spin(forward);
}

// Change body speed
void faster() {
  speed = std::min(speed + 25, 75);
  speed = ((speed == 35) ? 75 : speed);
  print(speed);
}
void slower() {
  speed = std::max(speed - 25, 10);
  speed = ((speed == 50) ? 10 : speed);
  print(speed);
}

// Sleep function because the actual function is super annoying
void sleep(double t){
  vex::task::sleep(t);
} 

void pre_auton() {
  // Motors Resetting 
  // No Code needed in this section  
}

void autonomous() {
  
  /* Move forward program
  baseVelocity(75);
  moveTurns(2);
  vex::task::sleep(100);
  moveTurns(-2);
  vex::task::sleep(100);
  */

  // New Auton For Programming Skills
  int tile = 23;
  int wBar = 7;
  float block = 5.5;

  // Moving inches forward to activate the wheel bar 
  baseVelocity(50);
  moveInches(wBar);

  armsUp(2000);
  armsDown(1500);
  arms.stop();
  
  // Start intaking to move forward and get 5 blocks
  intake(100);
  moveInches(block * 5 + 1);
  sleep(200);
  intake(20);

  // Move backwards 
  moveInches(block * -4.5);

  // Turn to put blocks
  // (-a, b) for LEFT and inverse for RIGHT
  moveInches(-12,12);
  sleep(100);

  // Move forward to put blocks
  intake(20);
  moveInches(3);

  // Activate ramp
  stoptake();
  rampUp(2000);
  outtake(20);

  // Move a little bit forward slowly
  baseVelocity(10);
  moveInches(1);

  // Go backwards
  sleep(100);
  baseVelocity(75);
  moveInches(-10);
 
}

// Used to know when a button starts being pressed
bool upLastFrame = false;
bool downLastFrame = false;
bool xLastFrame = false;

void usercontrol() {
  while(1) {
    float Axis1 = -Controller1.Axis1.value();
    float Axis2 = -Controller1.Axis2.value();
    float Axis3 = Controller1.Axis3.value();
    float Axis4 = -Controller1.Axis4.value();

    // baseVelocity(speed);

    if(!Controller1.ButtonA.pressing()) {
      frontLeft.spin(directionType::fwd, (Axis3 - Axis1) * speed / 100, velocityUnits::pct);
      backLeft.spin(directionType::fwd, (Axis3 - Axis1) * speed / 100, velocityUnits::pct);
      frontRight.spin(directionType::fwd, (Axis3 + Axis1) * speed / 100, velocityUnits::pct);
      backRight.spin(directionType::fwd, (Axis3 + Axis1) * speed / 100, velocityUnits::pct);
    } else {
      frontLeft.spin(directionType::fwd, (Axis3 - Axis4) * speed / 100, velocityUnits::pct);
      backLeft.spin(directionType::fwd, (Axis3 - Axis4) * speed / 100, velocityUnits::pct);
      frontRight.spin(directionType::fwd, (Axis3 + Axis4) * speed / 100, velocityUnits::pct);
      backRight.spin(directionType::fwd, (Axis3 + Axis4) * speed / 100, velocityUnits::pct);

      ramp.setVelocity(100, percent);
      ramp.spin(directionType::fwd, Axis2 * 0.30, velocityUnits::pct);
    }

    // Get the current button states
    bool upPressing = Controller1.ButtonUp.pressing();
    bool downPressing = Controller1.ButtonDown.pressing();
    bool xPressing = Controller1.ButtonX.pressing();

    // If up just got pressed, speed up. If down just got pressed, speed up.
    if(upPressing && !upLastFrame) {
      faster();
    } else if(downPressing && !downLastFrame) {
      slower();
    }

    // Save current button state for next frame
    upLastFrame = upPressing;
    downLastFrame = downPressing;
    xLastFrame = xPressing;

    // L1 raises the arms up, L2 lowers them
    if(Controller1.ButtonL2.pressing()) {
      arms.setVelocity(100, percent);
      arms.spin(forward);
    } else if(Controller1.ButtonL1.pressing()) {
      arms.setVelocity(100, pct);
      arms.spin(reverse);
    } else {
      arms.stop();  
    }

    // R1 intakes and R2 outtakes
    if(Controller1.ButtonR2.pressing()) {
      intake(speed);
    } else if(Controller1.ButtonR1.pressing()) {
      outtake(speed);
    } else {
      stoptake();
    }

    // Print debug info
    if(Brain.Screen.pressing()) {
      /*Brain.Screen.clearScreen();
      printBrain("Ramp:", 1, 1);
      printBrain("Arms:", 1, 2);
      printBrain(round(Potentiometer.angle(degrees)*1.005)-1, 6, 1);
      printBrain(round(PotentiometerH.angle(degrees)*1.005)-1, 6, 2);*/
    }

    task::sleep(20);
  }
}

int main() {

  vexcodeInit();

  Brain.Screen.clearScreen();
  

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  //Prevent main from exiting with an infinite loop.                        
  while(1) {
    task::sleep(100); //Sleep the task for a short amount of time to prevent wasted resources.
  }
}