#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor frontRight = motor(PORT10, ratio18_1, true);
motor frontLeft = motor(PORT20, ratio18_1, false);
motor backLeft = motor(PORT19, ratio18_1, false);
motor backRight = motor(PORT11, ratio18_1, true);
controller Controller1 = controller(primary);
motor intakeLeft = motor(PORT2, ratio18_1, false);
motor intakeRight = motor(PORT1, ratio18_1, true);
motor arms = motor(PORT5, ratio18_1, false);
/*vex-vision-config:begin*/
signature Vision__ORANGE_CUBE = signature (1, 5231, 7655, 6443, -1505, -525, -1015, 4.2, 0);
signature Vision__GREEN_CUBE = signature (2, -7495, -5101, -6298, -4927, -2581, -3754, 3.1, 0);
signature Vision__PURPLE_CUBE = signature (3, 1037, 1729, 1383, 7925, 11709, 9817, 5.1, 0);
vision Vision = vision (PORT13, 50, Vision__ORANGE_CUBE, Vision__GREEN_CUBE, Vision__PURPLE_CUBE);
/*vex-vision-config:end*/
pot potentiometer = pot(Brain.ThreeWirePort.A);
sonar ultrasonic = sonar(Brain.ThreeWirePort.C);
motor ramp = motor(PORT14, ratio18_1, false);
pot potentiometerH = pot(Brain.ThreeWirePort.H);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}