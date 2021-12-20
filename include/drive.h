#ifndef __DRIVE__
#define __DRIVE__

#include "vex.h"

extern void driveTheDamnRobot(void);
extern void resetGyro(void);
extern void stopAllDrive(brakeType);
extern void spinWheelsNoTracking(int, int, int, int);
extern float logDrive(float);
extern float logDriveT(float);
extern void spinRollers(int);
extern void stopRollers(brakeType);
extern void spinIntakes(int);
extern void spinIntakesRPM(directionType, int);
extern void stopIntakes(brakeType);
extern void driveStraightNoTracking(int);
extern void driveStraightNoTracking22(int);
extern float normalizer;
extern float mSpd[4];
extern double maxAxis, maxOutput;
extern float gyroAngle;
extern int joyX, joyY;
extern float joyZ;
extern float x2;
extern float y2;
extern float magnitude;
extern float angleTheta;

#endif //__DRIVE__