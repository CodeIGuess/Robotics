// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// frontRight          motor         10              
// frontLeft           motor         20              
// backLeft            motor         19              
// backRight           motor         11              
// Controller1          controller                    
// intakeLeft          motor         2               
// intakeRight         motor         1               
// arms                 motor         5               
// Vision               vision        13              
// Potentiometer        pot           A               
// Ultrasonic           sonar         C, D            
// ramp                 motor         14              
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
Tile Length:  ~24''
*/

#include "vex.h"
#include "robot-config.h"
#include "frame-class.h"

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
void print(char* n) {
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
  speed = n;
}
// Turns
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
// Degrees
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
// Inches
void moveInches(double n) {
  frontRight.spinFor(n*29, degrees, false);
  backRight.spinFor(n*29, degrees, false);
  frontLeft.spinFor(n*29, degrees, false);
  backLeft.spinFor(n*29, degrees);
}
void moveInches(double n1, double n2) {
  frontRight.spinFor(n2*29, degrees, false);
  backRight.spinFor(n2*29, degrees, false);
  frontLeft.spinFor(n1*29, degrees, false);
  backLeft.spinFor(n1*29, degrees);
}

// Ramp movement
void rampUp() {
  ramp.spin(forward);
}
void rampDown() {
  ramp.spin(reverse);
}
void rampStop() {
  ramp.stop();
}

// Arm movement
void armsUp() {
  arms.setVelocity(100, percent);
  arms.spin(forward);
}
void armsDown() {
  arms.setVelocity(100, pct);
  arms.spin(reverse);
}

// Intake movement
void intake(double p) {
  intakeLeft.setVelocity(p, percent);
  intakeRight.setVelocity(p, percent);
  intakeLeft.spin(reverse);
  intakeRight.spin(reverse);
}
void outtake(double p) {
  intakeLeft.setVelocity(p, percent);
  intakeRight.setVelocity(p, percent);
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

void pre_auton() {
  // Motors Resetting 
  // No Code needed in this section  
}

void autonomous() {
  // Auton variables
  double tile = 23;
  double robotLength = 12.5;
  double bonerLength = 8;

  // Set base velocity
  baseVelocity(10);

  // Move until wheels open
  moveInches(bonerLength);
  
  task::sleep(1000);

  moveInches(tile-bonerLength);

  baseVelocity(speedBase);
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

    if(!Controller1.ButtonA.pressing()) {
      frontLeft.spin(directionType::fwd, (Axis3 - Axis1) * speed / 100, velocityUnits::pct);
      backLeft.spin(directionType::fwd, (Axis3 - Axis1) * speed / 100, velocityUnits::pct);
      frontRight.spin(directionType::fwd, (Axis3 + Axis1) * speed / 100, velocityUnits::pct);
      backRight.spin(directionType::fwd, (Axis3 + Axis1) * speed / 100, velocityUnits::pct);

      // Stop ramp to make sure the motor doesn't overheat
      rampStop();
    } else {
      frontLeft.spin(directionType::fwd, (Axis3 - Axis4) * speed / 100, velocityUnits::pct);
      backLeft.spin(directionType::fwd, (Axis3 - Axis4) * speed / 100, velocityUnits::pct);
      frontRight.spin(directionType::fwd, (Axis3 + Axis4) * speed / 100, velocityUnits::pct);
      backRight.spin(directionType::fwd, (Axis3 + Axis4) * speed / 100, velocityUnits::pct);

      ramp.setVelocity(80, percent);
      ramp.spin(directionType::fwd, Axis2 * 0.9, velocityUnits::pct);
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
    if(Controller1.ButtonL1.pressing()) {
      armsUp();
    } else if(Controller1.ButtonL2.pressing()) {
      armsDown();
    } else {
      arms.stop();
    }

    // Set intake speed to 100 for safety
    intakeLeft.setVelocity(100, percent);
    intakeRight.setVelocity(100, percent);
    // R1 intakes and R2 outtakes
    if(Controller1.ButtonR1.pressing()) {
      intake(speed);
    } else if(Controller1.ButtonR2.pressing()) {
      outtake(speed);
    } else {
      stoptake();
    }

    // Print debug info
    if(Controller1.ButtonB.pressing()) {
      /*Brain.Screen.clearScreen();
      printBrain("Ramp:", 1, 1);
      printBrain("Arms:", 1, 2);
      printBrain(round(Potentiometer.angle(degrees)*1.005)-1, 6, 1);
      printBrain(round(PotentiometerH.angle(degrees)*1.005)-1, 6, 2);*/

      float temp = ramp.temperature(percent);
      if (temp > 90) {
        print("YOU'RE F*CKED");
      } else if (temp > 80) {
        print("Really, calm down");
      } else if (temp > 70) {
        print("Hot (sort of)");
      } else if (temp > 60) {
        print("Mmm, a little hot");
      } else if (temp > 50) {
        print("Pretty ok");
      } else if (temp > 40) {
        print("Perfect, tbh");
      } else if (temp > 30) {
        print("A little cold :)");
      } else if (temp > 20) {
        print("cold");
      } else if (temp > 10) {
        print("under-heating");
      } else {
        print("Freezing");
      }
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