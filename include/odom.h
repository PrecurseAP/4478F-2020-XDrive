#ifndef __ODOM__
#define __ODOM__
#include "vex.h"

extern thread ODOM;

extern float averageOrientation;
extern float rX;
extern float rY;

extern float globalOrientation;

void resetPos(void);

void updatePositionVars(void);

extern float wheelCirc;

extern float centerToLeft;
extern float centerToRight;
extern float centerToBack;

extern float deltaLeft;
extern float deltaRight;
extern float deltaBack;

extern float leftEnc;
extern float rightEnc;
extern float backEnc;

extern float prevLeft;
extern float prevRight;
extern float prevBack;

extern int tracking(void);

extern bool atPoint;

extern float kPx, kPy, kPt;
extern float kDx, kDy, kDt;

extern void moveToPoint(float, float, int, float, float, float);

#endif //_ODOM_