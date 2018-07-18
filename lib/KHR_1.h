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
 */

#ifndef KHR_1_H
#define KHR_1_H

#include "Arduino.h"
#include <StandardCplusplus.h>
#include <VarSpeedServo.h>
#include <string>
#include <vector>

// Arduino board pins
#define L_S_PITCH 2
#define R_S_PITCH 3
#define L_S_ROLL  4
#define R_S_ROLL  5
#define L_ELBOW   6
#define R_ELBOW   7
#define HEAD      8

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

class KHR_1
{
public:
	KHR_1();
	~KHR_1();

	// setup functions
	void attach();
	void detach();

	// Used to demonstrate what certain values do.

	// Hardcoded actions
	void left_wave();
	void right_wave();
	void both_wave();
	void stand();
	void robot_dance();
	void cheer();
	void flex_arms();

	// Semaphore a string, return false on invalid string
	// Valid string contains only letters and spaces
	bool semaphore(const std::string & s);
private:
	static const int default_speed = 0;
	static const int default_semaphore_delay = 1000;

	struct Pose
	{
		int left_s_pitch_angle, left_s_roll_angle, left_elbow_angle,
			right_s_pitch_angle, right_s_roll_angle, right_elbow_angle;

		Pose(int left_s_pitch_angle, int left_s_roll_angle, int left_elbow_angle,
			int	right_s_pitch_angle, int right_s_roll_angle, int right_elbow_angle);
	};

	struct Frame
	{
		Pose pose;
		int duration;
	};

	enum class SemaphoreSignal {LettersToFollow, NumbersToFollow, Attention, Rest, ReadyToReceive, Cancel};

	typedef std::vector<Frame> Animation;

	void animate(const Animation & animation);

	const Animation toSemaphoreAnimation(char signal) const;
	const Animation toSemaphoreAnimation(SemaphoreSignal signal) const;
	void pose(const Pose & pose, int speed = default_speed);

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
};

#endif
