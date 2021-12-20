#include "drive.h"
#include "vex.h"
#include "custommath.h"
#include "cmath"
#include "vex_timer.h"

//logarithmic drive function. this means that lower joystick values are skewed towards zero while higher ones still scale up to max speed.
float logDrive(float cv) {
  //less intense logarithmic drive, reaches high speeds at a good distance from joystick limits
  return pow(fabs(cv), 1.5) / (sign(cv)*sqrt(100));
}
float logDriveT(float cv) {
  //less intense logarithmic drive, reaches high speeds at a good distance from joystick limits
  return pow(fabs(cv), 1.5) / (sign(cv)*sqrt(50));
}
void stopAllDrive(brakeType bT) {
  /** 
   * Stops all drive motors with a specific brakeType.
   */
  backLeft.stop(bT);
  backRight.stop(bT);
  frontLeft.stop(bT);
  frontRight.stop(bT);
}

void spinRollers(int spd) {
  upperRollers.spin(forward, spd, percent);
  bottomRollers.spin(forward, spd, percent);
}

void stopRollers(brakeType bt) {
  upperRollers.stop(bt);
  bottomRollers.stop(bt);
}

void spinIntakes(int spd) {
  leftFlipOut.spin(forward, spd, percent);
  rightFlipOut.spin(forward, spd, percent);
}

void spinIntakesRPM(directionType dt, int spd) {
  leftFlipOut.spin(dt, spd, rpm);
  rightFlipOut.spin(dt, spd, rpm);
}


void stopIntakes(brakeType bt) {
  leftFlipOut.stop(bt);
  rightFlipOut.stop(bt);
}

void driveStraightNoTracking(int spd) {
  frontLeft.spin(forward, spd, percent);
  frontRight.spin(forward, -spd, percent);
  backRight.spin(forward, -spd, percent);
  backLeft.spin(forward, spd, percent);
}
void driveStraightNoTracking22(int spd) {
  frontLeft.spin(forward, spd, percent);
  frontRight.spin(forward, spd, percent);
  backRight.spin(forward, -spd, percent);
  backLeft.spin(forward, -spd, percent);
}

void spinWheelsNoTracking(int fL, int fR, int bR, int bL) {
  /**
   * Basic movement function to move all the drive motors at a certain speed. this is mainly used for imprecise forward, backward, left, and right movements.
   */
  frontLeft.spin(forward, fL, percent);
  frontRight.spin(forward, -fR, percent);
  backRight.spin(forward, -bR, percent);
  backLeft.spin(forward, bL, percent);
}

void resetGyro() {
  /**
   * Stops all drive motors then calibrates the gyro. I have to experiment with delays to make sure that the code only resumes when the gyro is done.
   */
  GYRO.calibrate();
  while(!GYRO.isCalibrating()) {
    wait(100, msec);
  }
}

timer turningTimer;

enum motorIndex {
  bL = 0,
  bR = 1,
  fR = 2,                 //enum to simplify human readability for motor speed indices in the motor speeds array
  fL = 3                  //this is probably a bad and convoluted solution to a non-problem but aiden does what he does
};

float mSpd[4];
float normalizer = 0;

void driveTheDamnRobot() {
  /**
   * Main drive function. Includes logarithmic and field centric drive.
   */
  while(1) {
    float gyroAngle = GYRO.heading(degrees);       //grab and store the gyro value, it is the orientation of the bot

    float joyX = logDrive(-Controller1.Axis4.position(percent));       // this is the left and right axis
    float joyY = logDrive(Controller1.Axis3.position(percent));      // this is the forward and backward axis
    float joyZ = logDriveT(Controller1.Axis1.position(percent)/2);    // this here is the turning axis.

    float magnitude = sqrt((joyX*joyX) + (joyY*joyY)) / M_SQRT2; //this calculates the magnitude of the direction vector of the joystick. 
    float angleTheta = atan2f(joyX, joyY) + (gyroAngle*(M_PI/180)); //this calculates the reference angle of the joystick coordinates offset by the gyro.

    float x2 = magnitude * cos(angleTheta);  //these two lines generate new robot centric values based on the magnitude of speed and the offset in angle.
    float y2 = magnitude * sin(angleTheta);

    mSpd[0] = x2 - y2 + joyZ;
    mSpd[1] = x2 + y2 + joyZ;
    mSpd[2] = -x2 - y2 + joyZ; //this is where the x, y, and turn components of holonomic movement are mushed together to calculate motor speeds.
    mSpd[3] = -x2 + y2 + joyZ;

    float maxAxis = MAX(fabs(joyX), fabs(joyY), fabs(joyZ)); //Find the maximum input given by the controller's axes and the angle corrector
    float maxOutput = MAX(fabs(mSpd[0]), fabs(mSpd[1]), fabs(mSpd[2]), fabs(mSpd[3])); //Find the maximum output that the drive program has calculated

    if (maxOutput == 0 || maxAxis == 0) {
      normalizer = 0; //Prevent the undefined value for normalizer
    } else {
      normalizer = maxAxis / maxOutput; //calculate normalizer
    }

    for (int i = 0; i <= 3; i++) {
      mSpd[i] *= normalizer; //caps motor speeds to the greatest input without losing the ratio between each speed, so as to not warp the direction of movement too much.
    }

    frontLeft.spin(forward, mSpd[0], percent);
    backLeft.spin(forward, mSpd[1], percent);
    frontRight.spin(forward, mSpd[2], percent);
    backRight.spin(forward, mSpd[3], percent);    //spin the motors at their calculated speeds.
   
    if(Controller1.ButtonR1.pressing()) {     //brings ball straight up and into tower
      spinIntakesRPM(forward, 200);
    } else {
      stopIntakes(hold);
    }
    if(Controller1.ButtonR2.pressing()) { //bring balls up, does not shoot them out
      spinIntakesRPM(reverse, 100);
    } else if (!Controller1.ButtonR1.pressing()) {
      stopIntakes(hold);
    }     
    if(Controller1.ButtonL1.pressing()) { //brings ball to hoarder cell, by spinning the roller above it backwards
      spinRollers(100);
    }
    if (Controller1.ButtonL2.pressing()) { 
      spinRollers(-100);
    } else if (!Controller1.ButtonL1.pressing()) {
      stopRollers(hold);
    }
    
    wait(10, msec); 
  }
}