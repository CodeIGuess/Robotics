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

using namespace vex;

competition Competition;
   
void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

void usercontrol( void ) {
  while (1) {
    
    float Axis1 = Controller1.Axis1.value();
    float Axis2 = Controller1.Axis2.value();
    float Axis3 = Controller1.Axis3.value();
    float Axis4 = Controller1.Axis4.value();

    front_left.spin(directionType::fwd, (Axis3 + Axis1)/2 - Axis4, velocityUnits::pct);
    back_left.spin(directionType::fwd, (Axis3 + Axis1)/2 + Axis4, velocityUnits::pct);

    front_right.spin(directionType::fwd, (Axis3 - Axis1)/2 + Axis4, velocityUnits::pct);
    back_right.spin(directionType::fwd, (Axis3 - Axis1)/2 - Axis4, velocityUnits::pct);

    if(Controller1.ButtonA.pressing()){

      Controller1.Screen.print("Brain B Is Working");

    }

    task::sleep(20);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

    // Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}