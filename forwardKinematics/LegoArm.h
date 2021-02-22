/*
 * Tufts University, Spring 2021
 * LegoArm.h
 * By: Sawyer Bailey Paccione and Joshua Fitzgerald
 * Completed:   February 21st,
 *
 * Description:   Represents a lego arm to be represented on the WIO Terminal
 *                Screen.
 */

#ifndef LegoArm_h
#define LegoArm_h

#include "Arduino.h"
#include <TFT_eSPI.h> // Hardware-specific library for Wio Terminal


class LegoArm
{
public:
  LegoArm();
  LegoArm(TFT_eSPI &tft, int x_start, int y_start, int arm_length, 
                  double arm_beta, uint32_t tft_color);

  void draw();
  void erase();

  void update_angle(double new_angle);
  void update_start_location(int x, int y);
  
  int get_endpositionx();
  int get_endpositiony();

private:
  void update_end_location();

  int START_LOCATION[2];
  int LENGTH;
  static const int THICKNESS = 3;
  uint32_t color;
  double beta;
  int end_location[2];

  TFT_eSPI *canvas;
};

#endif
