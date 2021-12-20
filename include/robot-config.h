using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial GYRO;
extern controller Controller1;
extern motor frontLeft;
extern motor frontRight;
extern motor backLeft;
extern motor backRight;
extern motor leftFlipOut;
extern motor rightFlipOut;
extern motor bottomRollers;
extern motor upperRollers;
extern encoder leftEncoder;
extern encoder rightEncoder;
extern encoder backEncoder;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );