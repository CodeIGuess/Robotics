// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         10              
// frontLeft           motor         20              
// back_left            motor         19              
// back_right           motor         11              
// Controller1          controller                    
// left_intake          motor         2               
// right_intake         motor         1               
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

// Base Variables
int speedBase = 75;
int speed = speedBase;

// Distance Variables
float rotations = 360;
double first_tile = 2.08 * rotations; //THIS MEASUREMENT IS NOT SET
double one_tile = 2.32 * rotations; //THIS MEASUREMENT IS NOT SET

void print(double n) 
{
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(n);
}
void print(double n, double cursorX, double cursorY) 
{
  Controller1.Screen.setCursor(cursorY, cursorX);
  Controller1.Screen.print(n);
}
void print(char *n, double cursorX, double cursorY) 
{
  Controller1.Screen.setCursor(cursorY, cursorX);
  Controller1.Screen.print(n);
}
void printBrain(double n) 
{
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print(n);
}
void printBrain(double n, double cursorX, double cursorY) 
{
  Brain.Screen.setCursor(cursorY, cursorX);
  Brain.Screen.print(n);
}
void printBrain(char* n, double cursorX, double cursorY) 
{
  Brain.Screen.setCursor(cursorY, cursorX);
  Brain.Screen.print(n);
}

void clearScreen() 
{
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
}

// Auton Helper Functions™
void base_velocity(double n) 
{
  frontLeft.setVelocity(n, percent);
  front_right.setVelocity(n, percent);
  back_right.setVelocity(n, percent);
  back_left.setVelocity(n, percent);
}
void move_turns(double n) 
{
  front_right.rotateFor(n, turns, false);
  back_right.rotateFor(n, turns, false);
  frontLeft.rotateFor(n, turns, false);
  back_left.rotateFor(n, turns);
}
void moveTurns(double nl, double nr) 
{
  front_right.rotateFor(nr, turns, false);
  back_right.rotateFor(nr, turns, false);
  frontLeft.rotateFor(nl, turns, false);
  back_left.rotateFor(nl, turns);
}
void moveDegrees(double n) 
{
  front_right.spinFor(n, degrees, false);
  back_right.spinFor(n, degrees, false);
  frontLeft.spinFor(n, degrees, false);
  back_left.spinFor(n, degrees);
}
void moveDegrees(double nl, double nr) 
{
  front_right.spinFor(nr, degrees, false);
  back_right.spinFor(nr, degrees, false);
  frontLeft.spinFor(nl, degrees, false);
  back_left.spinFor(nl, degrees);
}

// Ramp Movement
void rampUp() 
{
  ramp.spin(forward);
}
void rampDown() 
{
  ramp.spin(reverse);
}
void rampStop() 
{
  ramp.setVelocity(0, percent);
  ramp.spin(forward);
}

// Arm Movement
void up() 
{
  arms.setVelocity(100, percent);
  arms.spin(forward);
}
void down() 
{
  arms.setVelocity(100, pct);
  arms.spin(reverse);
}

// Intake Movement
void intake(double p) 
{
  left_intake.setVelocity(p * speed / 100, percent);
  right_intake.setVelocity(p, percent);
  left_intake.spin(forward);
  right_intake.spin(forward);
}
void outtake(double p) 
{
  left_intake.setVelocity(p * speed / 100, percent);
  right_intake.setVelocity(p * speed / 100, percent);
  left_intake.spin(reverse);
  right_intake.spin(reverse);
}
void stoptake() 
{
  left_intake.setVelocity(0, percent);
  right_intake.setVelocity(0, percent);
  left_intake.spin(forward);
  right_intake.spin(forward);
}

// Body speed control
void faster() 
{
  speed = std::min(speed + 25, 75);
  speed = ((speed == 35) ? 75 : speed);
  print(speed);
}
void slower()
{
  speed = std::max(speed - 25, 10);
  speed = ((speed == 50) ? 10 : speed);
  print(speed);
}

bool up_last_frame = false;
bool down_last_frame = false;
bool x_last_frame = false;

void pre_auton() 
{
  // Motors Resetting 
  // No Code needed in this section  
}

void autonomous() 
{
  // Variables for movement
  float tile = 2.32; // Changes depending on wheel size

  // Prepare Robot for Auton (Lift ramp)
  basevelocity(speedBase);
  up();
  task::sleep(1200);
  down();
  task::sleep(500);
  intake(75);
  task::sleep(500);
  
  // Get four blocks and return
  moveTurns(2*tile);
  task::sleep(100);
  stoptake();
  task::sleep(100);
}

void usercontrol() 
{
  while(1) 
  {
    
    float Axis1 = -Controller1.Axis1.value();
    float Axis2 = -Controller1.Axis2.value();
    float Axis3 =  Controller1.Axis3.value();
    float Axis4 = -Controller1.Axis4.value();

    // basevelocity(speed);

    if(!Controller1.ButtonA.pressing()) 
    {
      frontLeft.spin(directionType::fwd, (Axis3 - Axis1) * speed / 100, velocityUnits::pct);
      back_left.spin(directionType::fwd, (Axis3 - Axis1) * speed / 100, velocityUnits::pct);

      front_right.spin(directionType::fwd, (Axis3 + Axis1) * speed / 100, velocityUnits::pct);
      back_right.spin(directionType::fwd, (Axis3 + Axis1) * speed / 100, velocityUnits::pct);
    } else {
      frontLeft.spin(directionType::fwd, (Axis3 - Axis4) * speed / 100, velocityUnits::pct);
      back_left.spin(directionType::fwd, (Axis3 - Axis4) * speed / 100, velocityUnits::pct);

      front_right.spin(directionType::fwd, (Axis3 + Axis4) * speed / 100, velocityUnits::pct);
      back_right.spin(directionType::fwd, (Axis3 + Axis4) * speed / 100, velocityUnits::pct);

      ramp.setVelocity(100, percent);
      ramp.spin(directionType::fwd, Axis2*0.30, velocityUnits::pct);
    }

    bool up_pressing = Controller1.ButtonUp.pressing();
    bool down_pressing = Controller1.ButtonDown.pressing();
    bool x_pressing = Controller1.ButtonX.pressing();
    
    if(up_pressing && !up_last_frame) 
    {
      faster();
    } else if(down_pressing && !down_last_frame) {
      slower();
    }

    up_last_frame = up_pressing;
    down_last_frame = down_pressing;
    x_last_frame = x_pressing;

    // Arms
    if(Controller1.ButtonL1.pressing()) {up();}
    else if (Controller1.ButtonL2.pressing()) {down();}
    else {arms.stop();}
    
    // Intake Velocity
    if(Controller1.ButtonR2.pressing()) {outtake(speed);}
    else if (Controller1.ButtonR1.pressing()) {intake(speed);}
    else {stoptake();}

    if (Brain.Screen.pressing()) {
      /*Brain.Screen.clearScreen();
      printBrain("Ramp:", 1, 1);
      printBrain("Arms:", 1, 2);
      printBrain(round(Potentiometer.angle(degrees)*1.005)-1, 6, 1);
      printBrain(round(PotentiometerH.angle(degrees)*1.005)-1, 6, 2);*/
      Brain.Screen.clearScreen();
      printBrain("a", 1, 1);
      for (int a = 2; a < 13; a++) {
        printBrain("|.........|.........|.........|.........|.....|||||", 1, a);
      }
    }

    task::sleep(20);
  }
}

int main() 
{

    vexcodeInit();

    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) 
    {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}