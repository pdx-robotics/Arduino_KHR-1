/* 
 * Arduino_KHR1.cpp - Library to control the 
 * Kondo KHR_1.
 *
 * Created by Aaron Chan, April 11, 2018
 *
 * This prigram is ment to pervide some hardcoded functions 
 * for simple movements like waveing and standing.
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
*/

//#include "Arduino.h"//Redundant includes. "Arduino.h" is in "KHR_1.h"
#include "Arduino_KHR1.h"

// KHR_1 servos
VarSpeedServo left_s_pitch;
VarSpeedServo left_s_roll;
VarSpeedServo left_elbow;

VarSpeedServo right_s_pitch;
VarSpeedServo right_s_roll;
VarSpeedServo right_elbow;
/*
VarSpeedServo left_h_roll;
VarSpeedServo left_h_pitch;
VarSpeedServo left_knee;
VarSpeedServo left_a_pitch;
VarSpeedServo left_a_roll;

VarSpeedServo right_h_roll;
VarSpeedServo right_h_pitch;
VarSpeedServo right_knee;
VarSpeedServo right_a_pitch;
VarSpeedServo right_a_roll;
*/
VarSpeedServo head_pan;

/*
*Attaches all servo motors to an I/O pin defined in KHR_1.h.
*/
void attach_KHR_1(void)
{
    left_s_pitch.attach(L_S_PITCH);
    left_s_roll.attach(L_S_ROLL);
    left_elbow.attach(L_ELBOW);

    right_s_pitch.attach(R_S_PITCH);
    right_s_roll.attach(R_S_ROLL);
    right_elbow.attach(R_ELBOW);
/*
    left_h_roll.attach(L_H_ROLL);
    left_h_pitch.attach(L_H_PITCH);
    left_knee.attach(L_KNEE);
    left_a_pitch.attach(L_A_PITCH);
    left_a_roll.attach(L_A_ROLL);

    right_h_roll.attach(R_H_ROLL);
    right_h_pitch.attach(R_H_PITCH);
    right_knee.attach(R_KNEE);
    right_a_pitch.attach(R_A_PITCH);
    right_a_roll.attach(R_A_ROLL);
*/
    head_pan.attach(HEAD);
}
     
/*
*Stops all attached servos from pulsing their pins.
*/
void detach_KHR_1(void)
{
    left_s_pitch.detach();
    left_s_roll.detach();
    left_elbow.detach();

    right_s_pitch.detach();
    right_s_roll.detach();
    right_elbow.detach();
/*    
    left_h_roll.detach();
    left_h_pitch.detach();
    left_knee.detach();
    left_a_pitch.detach();
    left_a_roll.detach();

    right_h_roll.detach();
    right_h_pitch.detach();
    right_knee.detach();
    right_a_pitch.detach();
    right_a_roll.detach();
*/
    head_pan.detach();
}

/*
* Wave with left hand
*/
void left_wave(void)
{
    left_s_pitch.write(150,50);
    left_s_roll.write(0,50);

    delay(1500);
    left_elbow.write(110,70,true);
    left_elbow.write(70,70,true);
    left_elbow.write(110,70,true);
    left_elbow.write(70,70,true);

    left_elbow.write(80,50);
    left_s_pitch.write(10,50);
    left_s_roll.write(10,50);
    delay(1000);
}

/*
* Wave with right hand
*/
void right_wave(void)
{
    right_s_pitch.write(30,50);
    right_s_roll.write(160,50);
  
    delay(1500);
    right_elbow.write(110,70,true);
    right_elbow.write(70,70,true);
    right_elbow.write(110,70,true);
    right_elbow.write(70,70,true);
    
    right_elbow.write(90,50);
    right_s_pitch.write(170,50);
    right_s_roll.write(160,50);
    delay(1000);
}

/*
*Wave both hands at the same time.
*/
void both_wave()
{
	left_s_pitch.write(150,50);
	right_s_pitch.write(30,50);
    left_s_roll.write(0,50);
	right_s_roll.write(160,50);
	
    delay(1500);
    left_elbow.write(110,70);
	right_elbow.write(110,70,true);
    left_elbow.write(70,70);
	right_elbow.write(70,70,true);
    left_elbow.write(110,70);
	right_elbow.write(110,70,true);
    left_elbow.write(70,70);
	right_elbow.write(70,70,true);

    left_elbow.write(80,50);
	right_elbow.write(90,50);
    left_s_pitch.write(10,50);
	right_s_pitch.write(170,50);
    left_s_roll.write(10,50);
	right_s_roll.write(160,50);
    delay(1000);
}