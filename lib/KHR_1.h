/*
 * KHR_1.h - Library to control the Kondo KHR_1.
 *
 * The KHR_1 servo channels have been renumbered for this Arduino
 * implementation using the PCA9865 Servo Driver. 
 *
 * Because the servo driver can only support 16 servos,
 * we will control the head with a pin on the Arduino board.
 *
 * | Part           | Left  | Right |
 * |================|=======|=======|
 * | Shoulder Pitch |   0   |  15   |
 * | Shoulder Roll  |   1   |  14   |
 * | Elbow          |   2   |  13   |
 * | Hip Roll       |   3   |  12   |
 * | Hip Pitch      |   4   |  11   |
 * | Knee           |   5   |  10   |
 * | Ankle Pitch    |   6   |   9   |
 * | Ankle Roll     |   7   |   8   |
 * | Head Pan       |  ??   |
 * 
 * Created by Aaron Chan, April 11, 2018
 * Semaphore by Ha Ly
 * Modified by Aaron Chan, July 28, 2018
 */

#ifndef KHR_1_H
#define KHR_1_H

#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>
#include <StandardCplusplus.h>
#include <string>
#include <vector>

// Servo Driver Channels
#define R_S_PITCH 15
#define R_S_ROLL  14
#define R_ELBOW   13
#define R_H_ROLL  12
#define R_H_PITCH 11
#define R_KNEE    10 
#define R_A_PITCH  9
#define R_A_ROLL   8

#define L_S_PITCH  0
#define L_S_ROLL   1
#define L_ELBOW    2 
#define L_H_ROLL   3
#define L_H_PITCH  4
#define L_KNEE     5
#define L_A_PITCH  6
#define L_A_ROLL   7

//#define HEAD      

// Range of values to work with KRS-784 ICS servos
#define DMAX 530
#define DMIN 160
#define FREQ 60
#define MAP(d) map(d,0,180, DMIN, DMAX)
#define DWRITE(channel, d) pwm.setPWM(channel,0,MAP(d))

class KHR_1
{
public:
	KHR_1();
	~KHR_1();

    void init();
    void stand();
/*
	// Used to demonstrate what certain values do.

	// Hardcoded actions
	void left_wave();
	void right_wave();
	void both_wave();
	void stand();
*/
	/* Semaphore a string, return false on invalid string
	 * Valid string contains only letters (upper and lowercase) and spaces
	 * Optional parameter to disable "Attention" (start) and "Ready to Receive" (end) signals
	 */
	bool semaphore(const std::string & s, bool enableStartEndAnimations = true);
private:
	static const int default_semaphore_delay = 1000;

	struct Pose
	{
		char left_s_pitch_angle, left_s_roll_angle, left_elbow_angle,
		    left_h_roll_angle, left_h_pitch_angle, left_knee_angle,
			left_a_pitch_angle, left_a_roll_angle,
			right_s_pitch_angle, right_s_roll_angle, right_elbow_angle,
			right_h_roll_angle, right_h_pitch_angle, right_knee_angle,
			right_a_pitch_angle, right_a_roll_angle;
	};

	struct Frame
	{
		Pose pose;
		int duration;
	};

	enum class SemaphoreSignal
	{
		LettersToFollow,
		NumbersToFollow,
		Attention,
		Rest,
		ReadyToReceive,
		Cancel,
		BetweenSameLetters
	};

	typedef std::vector<Frame> Animation;

	void animate(const Animation & animation);

	const Animation toSemaphoreAnimation(char signal) const;
	const Animation toSemaphoreAnimation(SemaphoreSignal signal) const;
	void pose(const Pose & pose);

    // KHR-1 servo control
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
};

#endif
