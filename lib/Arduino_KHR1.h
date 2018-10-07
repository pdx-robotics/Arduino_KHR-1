/* 
 * Arduino_KHR1.h - Library to control the 
 * Kondo KHR_1.
 *
 * Created by Aaron Chan, April 11, 2018
 * Edited by William Brines, Oct 07, 2018 
 *
 * The KHR_1 servo channels have been renumbered for this Arduino
 * implementation. These numbers do not necessarily correspond 
 * with physical pins on the board:
 *
 * | Part           | Right | Left  |
 * |================|=======|=======|
 * | Shoulder Pitch |   1   |   2   |
 * | Shoulder Roll  |   3   |   4   |
 * | Elbow          |   5   |   6   |
 * | Hip Roll       |   7   |   8   |
 * | Hip Pitch      |   9   |  10   |
 * | Knee           |  11   |  12   |
 * | Ankle Pitch    |  13   |  14   |
 * | Ankle Roll     |  15   |  16   |
 * | Head Pan       |  17   |
 *
*/
#ifndef KHR_1_h
#define KHR_1_h

#include "Arduino.h"
#include <VarSpeedServo.h>

// Arduino board pins
//L - Left
//R - Right
//S - Shoulder
//H - Hip
//A - Ankle
#define R_S_PITCH 1
#define L_S_PITCH 2
#define R_S_ROLL  3
#define L_S_ROLL  4
#define R_ELBOW   5
#define L_ELBOW   6

/*
#define R_H_ROLL 7
#define L_H_ROLL 8
#define R_H_PITCH 9
#define L_H_PITCH 10
#define R_KNEE 11
#define L_KNEE 12
#define R_A_PITCH 13
#define L_A_PITCH 14
#define R_A_ROLL 15
#define L_A_ROLL 16
*/
#define HEAD 8 // 17 when the VarSpeedServo is fixed to have more servos.

// setup functions
void attach_KHR_1(void);
void detach_KHR_1(void);

// Used to demonstrate what certain values do.

// Hardcoded actions
void left_wave(void);//Waves left limbs.
void right_wave(void);//Waves right limbs.
void both_wave();//Waves both right and left limbs.

/*Not implemented.
void stand(void);
void robot_dance(void);
void cheer(void);
void flex_arms(void);
*/

// KHR_1 servos 
extern VarSpeedServo left_s_pitch;
extern VarSpeedServo left_s_roll;
extern VarSpeedServo left_elbow;

extern VarSpeedServo right_s_pitch;
extern VarSpeedServo right_s_roll;
extern VarSpeedServo right_elbow;
/*
extern VarSpeedServo left_h_roll;
extern VarSpeedServo left_h_pitch;
extern VarSpeedServo left_knee;
extern VarSpeedServo left_a_pitch;
extern VarSpeedServo left_a_roll;

extern VarSpeedServo right_h_roll;
extern VarSpeedServo right_h_pitch;
extern VarSpeedServo right_knee;
extern VarSpeedServo right_a_pitch;
extern VarSpeedServo right_a_roll;
*/
extern VarSpeedServo head_pan;
   
#endif
