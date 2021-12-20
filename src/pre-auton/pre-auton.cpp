#include "vex.h"
#include "pre-auton.h"

enum autonSquare {
  leftRed,
  rightRed,
  leftBlue,               //enum to simplify human readability of autonomous start positions
  rightBlue,
  none
};

struct preautonStats {
  int tx;
  int ty;                             //structure to act as a container for touch screen variables
  autonSquare touchedSquare = none;
  bool autSel = false;
} p;

void drawGoal(int x, int y, color ballColor) {
  /* this draws a black circle filled with a colored ball in the middle, looks exactly like a goal from top down */
  /* give color::transparent for ballC to make a goal with no ball */
  Brain.Screen.drawCircle(x, y, 9, color::transparent);
  Brain.Screen.drawCircle(x, y, 8, color::transparent);
  Brain.Screen.drawCircle(x, y, 7, color::transparent);
  Brain.Screen.drawCircle(x, y, 6, ballColor);
}

void renderScreen() {
  //for reference the screen is 480 x 272 pixels
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor("#777777"); //change border color of squares to a slightly darker gray, separates tiles
    
  for (int ROW = 0; ROW < 6; ROW++) 
    for (int COL = 0; COL < 6; COL++) 
      Brain.Screen.drawRectangle( (COL * 35) + 133 , (ROW * 35) + 18 , 35 , 35 , "#888888");
  //^^ The above nested loop generates the 6x6 grid of field tiles in gray

  switch(p.touchedSquare) {
    case leftRed:
      Brain.Screen.drawRectangle(133, 53, 35, 35, color::white); break;
    case rightRed:
      Brain.Screen.drawRectangle(133, 158, 35, 35, color::white); break;                                                                        
    case leftBlue:                                                          //logic to highlight the square that was pressed
      Brain.Screen.drawRectangle(308, 158, 35, 35, color::white); break;
    case rightBlue:
      Brain.Screen.drawRectangle(308, 53, 35, 35, color::white); break;
    default: break;
      //do nothing if there is no chosen square
  }

  Brain.Screen.setPenColor(color::red);
  Brain.Screen.drawRectangle(113, 20, 3, 205, color::red);   //draw leftmost red line

  Brain.Screen.setPenColor(color::blue);
  Brain.Screen.drawRectangle(363, 20, 3, 205, color::blue);  //draw rightmost blue line 

  Brain.Screen.setPenColor(color::white); //change to white

  Brain.Screen.drawRectangle(133, 120, 35, 2);               //draw two horizontal white lines on the left
  Brain.Screen.drawRectangle(133, 124, 35, 2);               //
                                                
  Brain.Screen.drawRectangle(167, 18, 2, 209);               //draw vertical white line on the left

  Brain.Screen.drawRectangle(235, 18, 2, 209);               //draw two vertical white lines in the center                                  
  Brain.Screen.drawRectangle(239, 18, 2, 209);               //

  Brain.Screen.drawRectangle(307, 18, 2, 209);               //draw vertical white line on the right

  Brain.Screen.drawRectangle(308, 120, 34, 2);               //draw two horizontal white lines on the right                                                                                    
  Brain.Screen.drawRectangle(308, 124, 34, 2);               //

  Brain.Screen.setPenColor("#444444"); //change color to a dark gray

  Brain.Screen.drawRectangle(133, 18, 209, 2); //
  Brain.Screen.drawRectangle(133, 226, 209, 2);//     Draw field border walls in dark gray
  Brain.Screen.drawRectangle(133, 18, 2, 209); //                                                
  Brain.Screen.drawRectangle(341, 18, 2, 209); //

  Brain.Screen.setPenColor("#222222"); //set color to a very dark gray, pretty much black

  drawGoal(144, 29, color::blue);              //                
  drawGoal(238, 29, color::red);               //draw top three goals
  drawGoal(331, 29, color::red);               //

  drawGoal(144, 123, color::blue);             // 
  drawGoal(238, 123, color::transparent);      //draw middle three goals
  drawGoal(331, 123, color::red);              //

  drawGoal(144, 216, color::blue);             // 
  drawGoal(238, 216, color::blue);             //draw bottom three goals
  drawGoal(331, 216, color::red);              //

  Brain.Screen.drawCircle(155, 40, 6, color::red);
  Brain.Screen.drawCircle(320, 40, 6, color::blue);
  Brain.Screen.drawCircle(320, 205, 6, color::blue);
  Brain.Screen.drawCircle(155, 205, 6, color::red);
  Brain.Screen.drawCircle(238, 70, 6, color::red);          //DRAW ALL THE DAMN BALLS )that arent in goals(
  Brain.Screen.drawCircle(238, 175, 6, color::blue);
  Brain.Screen.drawCircle(238, 107, 6, color::red);
  Brain.Screen.drawCircle(238, 139, 6, color::blue);
  Brain.Screen.drawCircle(222, 123, 6, color::blue);
  Brain.Screen.drawCircle(254, 123, 6, color::red);

  if (p.autSel == false) { 
    Brain.Screen.drawRectangle(0, 0, 80, 272, "#007F00");       //Draw left and right confirmation buttons
    Brain.Screen.drawRectangle(400, 0, 80, 272, "#007F00");
  }
  else {
    Brain.Screen.drawRectangle(0, 0, 80, 272, "#00007F");       //Draw left and right unconfirmation buttons
    Brain.Screen.drawRectangle(400, 0, 80, 272, "#00007F");
  }
  Brain.Screen.printAt(4, 17, false, "Confirm");       //
  Brain.Screen.printAt(4, 234, false, "Confirm");      //     Draw confirm text on confirm buttons
  Brain.Screen.printAt(405, 17, false, "Confirm");     //
  Brain.Screen.printAt(405, 234, false, "Confirm");    //
}

void touchScreenLogic() {
  p.tx = Brain.Screen.xPosition();  // grab coordinates of the touch
  p.ty = Brain.Screen.yPosition();  //

  if (p.autSel == true) goto Render;

  //to make touching squares somewhat easier i included some adjacent tiles in the logic that when touched, count as one tile.
  if ((p.tx >= 133) && (p.tx <= 168)) {
    if ((p.ty >= 53) && (p.ty <= 121)) {               //is it the leftmost red-side position?
      p.touchedSquare = leftRed;
    }
    else if ((p.ty >= 123) && (p.ty <= 193)) {         //is it the rightmost red-side position?
      p.touchedSquare = rightRed;
    }
  }                                                           //these if statements are logic to determine which
  //                                                          //autonomous square was pressed, if any
  
  else if ((p.tx >= 308) && (p.tx <= 343)) {
    if ((p.ty >= 53) && (p.ty <= 121)) {               //is it the rightmost blue-side position?
      p.touchedSquare = rightBlue;
    }
    else if ((p.ty >= 123) && (p.ty <= 193)) {         //is it the leftmost blue-side position?
      p.touchedSquare = leftBlue;
    }
  }

  else if (((p.tx <= 80) || (p.tx >= 400)) && (p.touchedSquare != none)) {
    p.autSel = p.autSel ? false : true;
  }
  Render: renderScreen();
}