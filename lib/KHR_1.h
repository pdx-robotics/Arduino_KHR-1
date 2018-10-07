/* 
 * KHR_1.h - Library to control the 
 * Kondo KHR_1.
 *
 * Created by Aaron Chan, April 11, 2018
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
#define L_S_PITCH 2
#define R_S_PITCH 3
#define L_S_ROLL  4
#define R_S_ROLL  5
#define L_ELBOW   6
#define R_ELBOW   7
/*
#define L_H_ROLL
#define R_H_ROLL
#define L_H_PITCH
#define R_H_PITCH
#define L_KNEE
#define R_KNEE
#define L_A_PITCH
#define R_A_PITCH
#define L_A_ROLL
#define R_A_ROLL
*/
#define HEAD      8

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
