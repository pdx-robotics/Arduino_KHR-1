/* 
 * KHR_1.cpp - Library to control the 
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
 *
*/
#include "Arduino.h"
#include "KHR_1.h"
#include <cctype>

KHR_1::KHR_1()
{
	// attach();
}

KHR_1::~KHR_1()
{
	detach();
}

void KHR_1::attach()
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

void KHR_1::detach()
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

// Wave with left hand
void KHR_1::left_wave()
{
	left_s_pitch.write(150, 50);
	left_s_roll.write(0, 50);

	delay(1500);
	left_elbow.write(110, 70, true);
	left_elbow.write(70, 70, true);
	left_elbow.write(110, 70, true);
	left_elbow.write(70, 70, true);

	left_elbow.write(80, 50);
	left_s_pitch.write(10, 50);
	left_s_roll.write(10, 50);
	delay(1000);
}

// Wave with right hand
void KHR_1::right_wave()
{
	right_s_pitch.write(30, 50);
	right_s_roll.write(160, 50);
	delay(1500);
	right_elbow.write(110, 70, true);
	right_elbow.write(70, 70, true);
	right_elbow.write(110, 70, true);
	right_elbow.write(70, 70, true);

	right_elbow.write(90, 50);
	right_s_pitch.write(170, 50);
	right_s_roll.write(160, 50);
	delay(1000);
}

void KHR_1::both_wave()
{
	left_s_pitch.write(150, 50);
	right_s_pitch.write(30, 50);
	left_s_roll.write(0, 50);
	right_s_roll.write(160, 50);

	delay(1500);
	left_elbow.write(110, 70);
	right_elbow.write(110, 70, true);
	left_elbow.write(70, 70);
	right_elbow.write(70, 70, true);
	left_elbow.write(110, 70);
	right_elbow.write(110, 70, true);
	left_elbow.write(70, 70);
	right_elbow.write(70, 70, true);

	left_elbow.write(80, 50);
	right_elbow.write(90, 50);
	left_s_pitch.write(10, 50);
	right_s_pitch.write(170, 50);
	left_s_roll.write(10, 50);
	right_s_roll.write(160, 50);
	delay(1000);
}

// WIP
KHR_1::Pose::Pose(int left_s_pitch_angle, int left_s_roll_angle, int left_elbow_angle,
	int right_s_pitch_angle, int right_s_roll_angle, int right_elbow_angle) :
		left_s_pitch_angle{left_s_pitch_angle + 90},
		left_s_roll_angle{- left_s_roll_angle + 90},
		left_elbow_angle{- left_elbow_angle + 90},
		right_s_pitch_angle{- right_s_pitch_angle + 90},
		right_s_roll_angle{right_s_roll_angle + 90},
		right_elbow_angle{right_elbow_angle + 90}
{}

// Check if string is valid, then semaphore each letter
bool KHR_1::semaphore(const std::string & s)
{
	for (auto ch : s)
	{
		if (!(std::isalpha(ch) || ch == ' '))
		{
			return false;
		}
	}
	/*
	for (auto ch : s)
	{
		semaphore(std::tolower(ch));
		delay(1000);
	}
	*/
	animate(stringToSemaphoreAnimation(s));
	return true;
}

const KHR_1::Pose KHR_1::charToPose(char ch) const
{
	// WIP Determine pose coordinates
	switch (ch)
	{
		case 'a':
			//return {0, 0, 90, 180, 135, 90};
			return {-90, 90, 0, -90, 45, 0};
			break;
		case 'b':
			//return {0, 0, 90, 90, 90, 90};
			return {-90, 90, 0, 0, 0, 0};
			break;
		case 'c':
			//return {0, 0, 90, 0, 135, 90};
			return {-90, 90, 0, 90, 45, 0};
			break;
		case 'd':
			//return {0, 0, 90, 0, 180, 90};
			return {-90, 90, 0, 90, 90, 0};
			break;
		case 'e':
			// return {180, 45, 90, 180, 180, 90};
			return {90, 45, 0, -90, 90, 0};
			break;
		case 'f':
			// return {180, 45, 90, 180, 180, 90};
			return {0, 0, 0, -90, 90, 0};
			break;
		case 'g':
			// return {180, 45, 90, 180, 180, 90};
			return {-90, 45, 0, -90, 90, 0};
			break;
		case 'j':
			return {0, 0, 0, 90, 90, 0};
			break;
		case 'k':
			return {90, 90, 0, -90, 45, 0};
			break;
		case 'l':
			return {90, 45, 0, -90, 45, 0};
			break;
		case 'm':
			return {0, 0, 0, -90, 45, 0};
			break;
		case 'n':
			return {-90, 45, 0, -90, 45, 0};
			break;
		default:
			return {90, 90, 90, 90, 90, 90};
			break;
	}
}

void KHR_1::pose(const KHR_1::Pose & pose, int speed = default_speed)
{
	left_s_pitch.write(pose.left_s_pitch_angle, speed, true);
	left_s_roll.write(pose.left_s_roll_angle, speed, true);
	left_elbow.write(pose.left_elbow_angle, speed, true);
	right_s_pitch.write(pose.right_s_pitch_angle, speed, true);
	right_s_roll.write(pose.right_s_roll_angle, speed, true);
	right_elbow.write(pose.right_elbow_angle, speed, true);
}

/*
void KHR_1::semaphore(char ch)
{
	pose(charToPose(ch));
}
*/

// WIP
const KHR_1::Animation KHR_1::stringToSemaphoreAnimation(const std::string & s) const
{
	Animation animation;
	
	/*
	for (auto ch : s)
	{
		// Add a frame with a 1s delay. Unchecked
		//animation.emplace_back(charToPose(std::tolower(ch)), 1000);
		animation.push_back({charToPose(std::tolower(ch)), 1000});
	}
	*/
	
	for (size_t i{0}; i < s.size(); i++)
	{
		if (s[i] == 'h')
		{
			animation.push_back({{0, 90, 0, 0, 0, 0}, 400});
			animation.push_back({{-45, 90, 45, 0, 0, 0}, 1000});
			animation.push_back({{0, 90, 0, 0, 0, 0}, 300});
		}
		else if (s[i] == 'i')
		{
			animation.push_back({{0, 90, 0, 0, 0, 0}, 400});
			animation.push_back({{-45, 90, 45, 90, 45, 0}, 1000});
			animation.push_back({{0, 90, 0, 0, 0, 0}, 300});
		}
		else
		{
			animation.push_back({charToPose(std::tolower(s[i])), 1000});
		}
	}

	return animation;
}

void KHR_1::animate(const Animation & animation)
{
	for (auto & frame : animation)
	{
		pose(frame.pose);
		delay(frame.duration);
	}
}
