using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor front_right;
extern motor front_left;
extern motor back_left;
extern motor back_right;
extern controller Controller1;
extern motor left_intake;
extern motor right_intake;
extern motor arms;
extern motor ramp;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );