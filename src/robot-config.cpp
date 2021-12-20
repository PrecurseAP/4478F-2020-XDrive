#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
inertial GYRO = inertial(PORT11);
controller Controller1 = controller(primary);
motor frontLeft = motor(PORT19, ratio18_1, false);
motor frontRight = motor(PORT2, ratio18_1, false);
motor backLeft = motor(PORT3, ratio18_1, false);
motor backRight = motor(PORT4, ratio18_1, false);
motor leftFlipOut = motor(PORT5, ratio18_1, false);
motor rightFlipOut = motor(PORT6, ratio18_1, true);
motor bottomRollers = motor(PORT7, ratio6_1, false);
motor upperRollers = motor(PORT20, ratio6_1, true);
encoder leftEncoder = encoder(Brain.ThreeWirePort.E);
encoder rightEncoder = encoder(Brain.ThreeWirePort.A);
encoder backEncoder = encoder(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}