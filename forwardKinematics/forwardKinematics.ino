/*
 * Tufts University, Spring 2021
 * forwardkinematics.ino
 * By: Sawyer Bailey Paccione and Joshua Fitzgerald
 * Completed:   February 21st,
 *
 * Description:  
 */
#include "LegoArm.h"
#include <TFT_eSPI.h>


/*******************************************************************************
*                            Define Known Constants                            *
*******************************************************************************/

const double L1       = 50;     // Length of the Smaller Arm
const double L2       = 70;     // Length of the Larger Arm
const double a        = 10;     // Distance Between Motors
const int ORIGIN[2]   = {160, 200}; // x,y pixel location on WIO of origin
const uint32_t BACKGROUND_COLOR = TFT_WHITE;


/*******************************************************************************
*                               Global Variables                               *
*******************************************************************************/

double b1 = 45*PI/180;  // First Angle of Motor on the Right
double b2 = 135*PI/180; // First Angle of Motor on the Left
double b3; // Second Angle of Motor on the Right
double b4; // Second Angle of Motor on the Left
TFT_eSPI tft;


/*******************************************************************************
*                             Define The Four Arms                             *
*******************************************************************************/

LegoArm left_short  = LegoArm(tft, ORIGIN[0] - a/2, ORIGIN[1], 
                              L1, b2, TFT_PINK);
LegoArm right_short = LegoArm(tft, ORIGIN[0] + a/2, ORIGIN[1], 
                              L1, b1, TFT_PINK);
LegoArm left_long   = LegoArm(tft, left_short.get_endpositionx(), 
                              left_short.get_endpositiony(), L2, 0,TFT_BLACK);
LegoArm right_long  = LegoArm(tft, right_short.get_endpositionx(), 
                              right_short.get_endpositiony(), L2, 0,TFT_BLACK);


/*******************************************************************************
*                                Main Functions                                *
*******************************************************************************/

/*
 * setup
 * Purpose:     The code here initializes important values and runs only once
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     The Wio Screen - FIll The Screen
 *              Communications between SPIKE and WIO (Serial1)
 *              Communication with Arduino Serial Port (Serial)
 * Notes:       
 */
void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(BACKGROUND_COLOR);
  Serial.begin(9600);
  Serial1.begin(9660);
  delay(1000);
  drawArms();
}

/*
 * loop
 * Purpose:     Will continuously run drawing the lines if updated reading from
 *              the SPIKE
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     The Wio Screen - Draws Lines
 *              Communications between SPIKE and WIO (Serial1)
 *              Communication with Arduino Serial Port (Serial)
 * Notes:       
 */
void loop() {
  while(Serial1.available()) {
    String line = Serial1.readStringUntil('\n');
    Serial.println(line);
    parseSpikeMessage(line);
    drawArms();
  }
}

/*******************************************************************************
*                               Helper Functions                               *
*******************************************************************************/

/*
 * findBeta3_4
 * Purpose:     Calculates the angle of the longer arms relative to the 
 *              smaller arms 
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     b3 and b4
 * Notes:       Adapted from Chris Roger's LabVIEW
 */
void findBeta3_4() {
  double A,B,C;
  double L, theta, sigma, gamma2, gamma1;
  double tempb2;
  
  tempb2 = PI - b2;
  
  A     = (L1/L2)*(sin(b1) - sin(tempb2));
  B     = a/L2+L1*(cos(b1) + cos(tempb2))/L2;
  L     = sqrt(sq(A)+sq(B));
  theta = atan2(A,B);
  C     = (2-sq(L))/2;
  
  sigma   = atan2(sqrt(1-sq(C)),C);
  gamma2  = 0.5*(PI - sigma + 2*theta);
  gamma1  = gamma2 -2*theta;
  
  b3 = PI-gamma1;
  b4 = gamma2;
}


/*
 * parseSpikeMessage
 * Purpose:     Parse a message from SPIKE PRIME into usuable angles 
 * Arguments:   msg (STRING) - The message from SPIKE
 * Returns:     N/A (void)
 * Effects:     
 * Notes:       The message is of the form "L180R180"
 */
void parseSpikeMessage(String msg) {
  // Parse Mesasge Into the Two Angles and store them in doubles
  String angle1_s, angle2_s;


  //Parse the Right angle
  int r_index = msg.indexOf('R');
  if (r_index != -1) {
    angle1_s = msg.substring(r_index+1);
  } else {
    return;
  }

  // Parse the left angle
  int l_index = msg.indexOf('L');
  if (l_index != -1) {
    angle2_s = msg.substring(l_index+1, r_index);
  } else {
    return;
  }
  // Erase Lines to make room 
  eraseAllArms();
  drawBlueDot();

  // Finish translation into angles
  b1 = angle1_s.toDouble()*PI/180;
  b2 = angle2_s.toDouble()*PI/180;

  // Update Angles of Short Arms
  right_short.update_angle(b1);
  left_short.update_angle(b2);
  
  // Update start point of long arms
  left_long.update_start_location(left_short.get_endpositionx(), 
                                    left_short.get_endpositiony());
  right_long.update_start_location(right_short.get_endpositionx(), 
                                    right_short.get_endpositiony());

  // Draw
  drawArms();
}

/*
 * eraseAllArms
 * Purpose:     Erases all of the arms exactly 
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     The WIO Screen
 * Notes:       Erases by drawing white, this needs to be changed if the 
 *              background color is changed
 */
void eraseAllArms() {
  left_short.erase();
  right_short.erase();
  left_long.erase();
  right_long.erase();
}

/*
 * drawBlueDot
 * Purpose:     Draws a blue dot at the tip of the robots arm
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     The WIO Screen
 * Notes:       
 */
void drawBlueDot() {
  int x = right_long.get_endpositionx();
  int y = right_long.get_endpositiony();

  tft.fillCircle(x, y, 2, TFT_BLUE);
  
}

/*
 * drawArms
 * Purpose:     Draws all of the arms of the robots after the angles have 
 *              been updated
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     The WIO Screen
 * Notes:       
 */
void drawArms() {
  left_short.draw();
  right_short.draw();
  findBeta3_4();
  Serial.println(b3);
  Serial.println(b4);
  left_long.update_angle(b4);
  right_long.update_angle(b3);
  left_long.draw();
  right_long.draw();
}
