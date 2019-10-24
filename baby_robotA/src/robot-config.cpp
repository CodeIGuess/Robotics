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
/*vex-vision-config:begin*/
signature Vision__ORANGE_CUBE = signature (1, 5231, 7655, 6443, -1505, -525, -1015, 4.2, 0);
signature Vision__GREEN_CUBE = signature (2, -7495, -5101, -6298, -4927, -2581, -3754, 3.1, 0);
signature Vision__PURPLE_CUBE = signature (3, 1037, 1729, 1383, 7925, 11709, 9817, 5.1, 0);
signature Vision__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision = vision (PORT13, 50, Vision__ORANGE_CUBE, Vision__GREEN_CUBE, Vision__PURPLE_CUBE, Vision__SIG_4, Vision__SIG_5, Vision__SIG_6, Vision__SIG_7);
/*vex-vision-config:end*/
pot Potentiometer = pot(Brain.ThreeWirePort.A);
sonar Ultrasonic = sonar(Brain.ThreeWirePort.C);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}