#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor front_right = motor(PORT11, ratio18_1, false);
motor front_left = motor(PORT20, ratio18_1, true);
motor back_left = motor(PORT10, ratio18_1, true);
motor back_right = motor(PORT1, ratio18_1, false);
controller Controller1 = controller(primary);
motor left_intake = motor(PORT19, ratio18_1, false);
motor right_intake = motor(PORT12, ratio18_1, true);
motor arm_right = motor(PORT5, ratio18_1, true);
motor arm_left = motor(PORT6, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}