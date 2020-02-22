#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor backRight = motor(PORT10, ratio18_1, true);
motor frontRight = motor(PORT9, ratio18_1, true);
motor backLeft = motor(PORT8, ratio18_1, false);
motor frontLeft = motor(PORT7, ratio18_1, false);
motor ramp = motor(PORT2, ratio18_1, false);
motor arms = motor(PORT1, ratio18_1, false);
motor intakeLeft = motor(PORT11, ratio18_1, false);
motor intakeRight = motor(PORT4, ratio18_1, true);

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