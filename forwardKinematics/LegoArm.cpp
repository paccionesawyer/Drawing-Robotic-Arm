/*
 * Tufts University, Spring 2021
 * LegoArm.cpp
 * By: Sawyer Bailey Paccione and Joshua Fitzgerald
 * Completed:   February 21st,
 *
 * Description:  
 */

#include "Arduino.h"
#include "LegoArm.h"

/******************************************************************************
*                               Public  Members                               *
******************************************************************************/

/*
 * Basic Constructor
 * Purpose:     Initialize in case arguments are unknown (For Testing)
 * Arguments:   Nothing
 * Returns:     Nothing
 * Effects:     LegoArm values
 */
LegoArm::LegoArm()
{
  START_LOCATION[0] = 0;
  this->START_LOCATION[1] = 0;
  this->LENGTH = 100;
  this->beta = 90;
}

/*
 * Parameterized Constructor
 * Purpose:     Initialize values of the lego arm
 * Arguments:   tft    [TFT_eSPI]   The graphic class for the WIO Terminal 
 *                                  Screen (Passed By Reference)
 *              x_start     [int]   The x location of the start of the line
 *              y_start     [int]   The y location of the start of the line
 *              arm_length  [int]   The length of the robotic arm (pixels)
 *              arm_beta    [int]   The angle the arm makes with the x-axis
 *              tft_color   [uint32_t]   TFT code of the color  
 * Returns:     Nothing
 * Effects:     LegoArm values
 * Notes:       tft is passed by reference, it takes the same one initialized
 *              in the main code.
 */
LegoArm::LegoArm(TFT_eSPI &tft, int x_start, int y_start, int arm_length, 
                  double arm_beta, uint32_t tft_color) 
{
  this->canvas            = &tft;
  this->START_LOCATION[0] = x_start;
  this->START_LOCATION[1] = y_start;
  this->LENGTH            = arm_length;
  this->beta              = arm_beta;
  this->color             = tft_color;
  update_end_location();
}

/*
 * draw
 * Purpose:     Draws the lego arm on the WIO Terminal using the tft passed by 
 *              reference
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     canvas Screen
 * Notes:       
 */
void LegoArm::draw() {
  for(int i = 0; i < THICKNESS; ++i) {
    canvas->drawLine(START_LOCATION[0]+i, START_LOCATION[1], end_location[0]+i, 
                    end_location[1], color);
  }
                    
}

/*
 * erase
 * Purpose:     erases the line exactly
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     the tft screen canvas
 * Notes:       
 */
void LegoArm::erase() {
  for(int i = 0; i < THICKNESS; ++i) {
    canvas->drawLine(START_LOCATION[0]+i, START_LOCATION[1], end_location[0]+i, 
                    end_location[1], TFT_WHITE);
  }
}

/*
 * update_angle
 * Purpose:     Updates the angle with a provided angle
 * Arguments:   new_angle [double]   The new angle
 * Returns:     N/A (void)
 * Effects:     Calls update_end_locations
 * Notes:       The angle is the independent variable, and the end locations is 
 *              dependent on it
 */
void LegoArm::update_angle(double new_angle) {
  this->beta = new_angle;
  update_end_location();
}

/*
 * update_start_location
 * Purpose:     Inputs given values to the related values of the LegoArm
 * Arguments:   x [int]   x-position of the start of the line
 *              y [int]   y-position of the start of the line
 * Returns:     N/A (void)
 * Effects:     start_locations
 * Notes:       
 */
void LegoArm::update_start_location(int x, int y) {
  START_LOCATION[0] = x;
  START_LOCATION[1] = y;
}

/*
 * get_endpositionx
 * Purpose:     Return the x-position of the end of the line
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     Values in LegoArm
 * Notes:       
 */
int LegoArm::get_endpositionx() {
  return end_location[0];
}

/*
 * get_endpositiony
 * Purpose:     Return the y-position of the end of the line
 * Arguments:   N/A
 * Returns:     N/A (void)
 * Effects:     Values in LegoArm
 * Notes:       
 */
int LegoArm::get_endpositiony() {
  return end_location[1];
}

/******************************************************************************
*                               Private Members                               *
******************************************************************************/
void LegoArm::update_end_location() {
  end_location[0] = START_LOCATION[0] + LENGTH*cos(beta);
  end_location[1] = START_LOCATION[1] - LENGTH*sin(beta);
}
