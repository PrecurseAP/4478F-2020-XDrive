#include "vex.h"
#include "robot-config.h"
#include "odom.h"
#include "drive.h"
#include "pre-auton.h"
#include "drive.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  renderScreen(); //draw the field on the screen once.
  Brain.Screen.pressed(touchScreenLogic); //callback so that the drawing and logic code is only executed when the screen is touched. (this saves tons of resources as opposed to a loop)
}

void autonomous(void) {
  //the moveToPoint function accepts (x, y, angle, xMult, yMult, tMult)
  //All of the arguments are measured in inches for distance, degrees for angles.

  thread ODOM = thread(tracking); //start position tracking loop
  
  resetPos(); //reset variables / initialize the values
/**
  moveToPoint(23, 6.7, 180, 7, 6, 1); //move in front of the middle home goal

  driveStraightNoTracking(60); //inch forward so the ball makes it

  wait(200, msec);
  
  stopAllDrive(hold); //stop drive to shoot
  
  spinRollers(100); //shoot the ball into the middle goal
  
  wait(850, msec);
  
  stopRollers(hold); //stop the rollers
  
  spinIntakes(100); //start intaking to flip them out and collect next balls

  moveToPoint(-21, 5, 226, 4, 4, 1); //move in front of left home row goal

  driveStraightNoTracking(27); //inch forward to collect ball and approach toward

  wait(700, msec);

  spinRollers(100); //start shooting

  wait(300, msec);  
  
  stopIntakes(hold); //stop intakes to not empty tower
  
  stopAllDrive(hold); //stop drive to shoot

  wait(1100, msec);
  
  stopRollers(hold);

  driveStraightNoTracking(-100); //zoom backwards so next move doesnt collide with tower
  
  wait(1100, msec);
  
  moveToPoint(64, 14, 135 , 3, 3, 1); //move in front of right home row tower
  
  spinIntakes(100); //start intaking
  
  driveStraightNoTracking(30); //inch forward to reacht he tower and collect ball
  
  wait(300, msec);
  
  spinRollers(100); //start shooting
  
  wait(1100, msec);
  
  stopIntakes(hold); //stop intakes to not empty tower
  
  stopAllDrive(hold); //stop drive to shoot
**/
  spinIntakes(100);
  wait(1000, msec);
  spinIntakes(-50);
  wait(600, msec);
  stopIntakes(hold);
  moveToPoint(0, 14, -135, 3, 5, 1);
  driveStraightNoTracking(30);
  wait(1000, msec);
  stopAllDrive(hold);
  spinRollers(100);
  wait(1100, msec);
  stopRollers(hold);
  moveToPoint(0, 22.5, -90, 3, 5, 1);
  spinIntakes(100);
  driveStraightNoTracking(30);
  spinRollers(100);
  wait(475, msec);
  stopAllDrive(hold);
  wait(1200, msec);
  stopIntakes(hold);
  stopRollers(hold);
  moveToPoint(39.8, 41.5, 0, 3, 3, 1);
  driveStraightNoTracking(20);
  wait(1100, msec);
  driveStraightNoTracking(-30);
  wait(900, msec);
  stopAllDrive(hold);
  spinIntakes(-50);
  wait(700, msec);
  stopIntakes(hold);
  /*driveStraightNoTracking22(30);
  wait(350, msec);*/
  moveToPoint(rX+4.5, rY, -3, 4, 3, 1);
  driveStraightNoTracking(30);
  wait(1500, msec);
  stopAllDrive(hold);
  spinRollers(100);
  wait(1000, msec);
  stopRollers(hold);
  moveToPoint(67, 40, 0, 3, 3, 1);
  /*moveToPoint(78, 81, -5, 3, 3, 1);
  spinIntakes(100);
  spinRollers(50);
  wait(500, msec);*/
  driveStraightNoTracking(30);
  wait(900, msec);
  //stopAllDrive(hold);
  spinIntakes(75);
  spinRollers(60);
  wait(1200, msec);
  stopRollers(hold);
  stopIntakes(hold);
  stopAllDrive(hold);
  spinIntakes(-50);
  wait(500, msec);
  stopIntakes(hold);
  moveToPoint(86, 114, 45, 3, 3, 1);
  driveStraightNoTracking(40);
  wait(1100, msec);
  spinRollers(100);
  wait(1500, msec);
  driveStraightNoTracking(-50);
  wait(1200, msec);
  spinIntakes(50);
  wait(500, msec);
  stopIntakes(hold);
  stopRollers(hold);
  moveToPoint(rX, rY, 90, 3, 3, 1);
  driveStraightNoTracking22(-30);
  wait(2500, msec);
  stopAllDrive(hold);
  resetPos();
  moveToPoint(27, 0, 0, 3, 3, 1);
  driveStraightNoTracking(40);
  spinIntakes(100);
  spinRollers(50);
  wait(2700, msec);
  stopAllDrive(hold);
  stopRollers(hold);
  spinIntakes(-50);
  wait(500, msec);
  moveToPoint(63, 0, 0, 3, 3, 1);
  driveStraightNoTracking(30);
  wait(2000, msec);
  spinRollers(100);

  //gimme four ball
}

void usercontrol(void) {
  ODOM.thread::interrupt();
  Controller1.ButtonX.pressed(resetGyro);
  //user control 
  driveTheDamnRobot();
}

int main() {
  vexcodeInit();
  
  resetGyro();
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) { wait(100, msec); }
} 