using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor frontRight;
extern motor frontLeft;
extern motor backLeft;
extern motor backRight;
extern controller Controller1;
extern motor intakeLeft;
extern motor intakeRight;
extern motor arms;
extern signature Vision__ORANGE_CUBE;
extern signature Vision__GREEN_CUBE;
extern signature Vision__PURPLE_CUBE;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;
extern pot potentiometer;
extern sonar ultrasonic;
extern motor ramp;
extern pot potentiometerH;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );