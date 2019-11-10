using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor front_right;
extern motor front_left;
extern motor back_left;
extern motor back_right;
extern motor right_intake;
extern motor left_intake;
extern motor ramp;
extern motor arms;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );