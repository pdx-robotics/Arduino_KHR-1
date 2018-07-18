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
	// Check if string is valid
	for (auto ch : s)
	{
		if (!(std::isalnum(ch) || ch == ' '))
		{
			return false;
		}
	}

	animate(toSemaphoreAnimation(SemaphoreSignal::Attention)); // Begin signal

	// Signal if first character is a number
	if (std::isdigit(s[0]))
	{
		animate(toSemaphoreAnimation(SemaphoreSignal::NumbersToFollow));
	}
	
	for (size_t i{0}; i < s.size() - 1; i++)
	{
		animate(toSemaphoreAnimation(s[i]));

		if (std::isalpha(s[i]) && std::isdigit(s[i + 1]))
		{
			animate(toSemaphoreAnimation(SemaphoreSignal::NumbersToFollow));
		}
		else if (std::isdigit(s[i]) && std::isalpha(s[i + 1]))
		{
			animate(toSemaphoreAnimation(SemaphoreSignal::LettersToFollow));
		}
	}

	animate(toSemaphoreAnimation(s.back())); // Last character
	animate(toSemaphoreAnimation(SemaphoreSignal::ReadyToReceive)); // End signal

	return true;
}

// const KHR_1::Pose KHR_1::toSemaphorePose(char ch) const
const KHR_1::Animation KHR_1::toSemaphoreAnimation(char signal) const
{
	// WIP Determine pose coordinates
	switch (signal)
	{
		case 'a':
		case '1':
			return {{{-90, 90, 0, -90, 45, 0}, default_semaphore_delay}};
			break;
		case 'b':
		case '2':
			return {{{-90, 90, 0, 0, 0, 0}, default_semaphore_delay}};
			break;
		case 'c':
		case '3':
			return {{{-90, 90, 0, 90, 45, 0}, default_semaphore_delay}};
			break;
		case 'd':
		case '4':
			return {{{-90, 90, 0, 90, 90, 0}, default_semaphore_delay}};
			break;
		case 'e':
		case '5':
			return {{{90, 45, 0, -90, 90, 0}, default_semaphore_delay}};
			break;
		case 'f':
		case '6':
			return {{{0, 0, 0, -90, 90, 0}, default_semaphore_delay}};
			break;
		case 'g':
		case '7':
			return {{{-90, 45, 0, -90, 90, 0}, default_semaphore_delay}};
			break;
		case 'h':
		case '8':
			return
			{
				{{0, 90, 0, 0, 0, 0}, 400},
				{{-45, 90, 45, 0, 0, 0}, default_semaphore_delay},
				{{0, 90, 0, 0, 0, 0}, 300}
			};
			break;
		case 'i':
		case '9':
			return
			{
				{{0, 90, 0, 0, 0, 0}, 400},
				{{-45, 90, 45, 90, 45, 0}, default_semaphore_delay},
				{{0, 90, 0, 0, 0, 0}, 300}
			};
			break;
		case 'j':
			return {{{0, 0, 0, 90, 90, 0}, default_semaphore_delay}};
			break;
		case 'k':
		case '0':
			return {{{90, 90, 0, -90, 45, 0}, default_semaphore_delay}};
			break;
		case 'l':
			return {{{90, 45, 0, -90, 45, 0}, default_semaphore_delay}};
			break;
		case 'm':
			return {{{0, 0, 0, -90, 45, 0}, default_semaphore_delay}};
			break;
		case 'n':
			return {{{-90, 45, 0, -90, 45, 0}, default_semaphore_delay}};
			break;
		case 'o':
			return
			{
				{{0, 90, 0, 0, 0, 0}, 400},
				{{45, 90, 45, 0, 0, 0}, default_semaphore_delay},
				{{0, 90, 0, 0, 0, 0}, 300}
			};
			break;
		case 'p':
			return {{{90, 90, 0, 0, 0, 0}, default_semaphore_delay}};
			break;
		case 'q':
			return {{{90, 45, 0, 0, 0, 0}, default_semaphore_delay}};
			break;
		case 'r':
			return {{{0, 0, 0, 0, 0, 0}, default_semaphore_delay}};
			break;
		case 's':
			return {{{-90, 45, 0, 0, 0, 0}, default_semaphore_delay}};
			break;
		case 't':
			return {{{90, 90, 0, 90, 45, 0}, default_semaphore_delay}};
			break;
		case 'u':
			return {{{90, 45, 0, 90, 45, 0}, default_semaphore_delay}};
			break;
		case 'v':
			return {{{-90, 45, 0, 90, 90, 0}, default_semaphore_delay}};
			break;
		case 'w':
			return
			{
				{{0, 0, 0, 0, 90, 0}, 400},
				{{0, 0, 0, 45, 90, 45}, default_semaphore_delay},
				{{0, 0, 0, 0, 90, 0}, 300}
			};
			break;
		case 'x':
			return
			{
				{{-90, 45, 0, 0, 90, 0}, 400},
				{{-90, 45, 0, 45, 90, 45}, default_semaphore_delay},
				{{-90, 45, 0, 0, 90, 0}, 300}
			};
			break;
		case 'y':
			return {{{0, 0, 0, 90, 45, 0}, default_semaphore_delay}};
			break;
		case 'z':
			return
			{
				{{0, 0, 0, 0, 90, 0}, 400},
				{{0, 0, 0, -45, 90, 45}, default_semaphore_delay},
				{{0, 0, 0, 0, 90, 0}, 300}
			};
			break;
		case ' ':
			return {{{-90, 90, 0, -90, 90, 0}, default_semaphore_delay}};
			break;
		default:
			return {{{0, 0, 0, 0, 0, 0}, 0}};
			break;
	}
}

const KHR_1::Animation KHR_1::toSemaphoreAnimation(KHR_1::SemaphoreSignal signal) const
{
	switch (signal)
	{
		case SemaphoreSignal::Attention:
			return
			{
				{{90, 45, 0, 90, 45, 0}, 500},
				{{-90, 45, 0, -90, 45, 0}, 500},
				{{90, 45, 0, 90, 45, 0}, 500},
				{{-90, 45, 0, -90, 45, 0}, 500},
				{{90, 45, 0, 90, 45, 0}, 500},
				{{-90, 45, 0, -90, 45, 0}, 500}
			};
			break;
		case SemaphoreSignal::ReadyToReceive:
			return
			{
				{{90, 90, 0, 90, 90, 0}, 500},
				{{-90, 90, 0, -90, 90, 0}, 500}
			};
			break;
		case SemaphoreSignal::LettersToFollow:
			return toSemaphoreAnimation('j');
			break;
		case SemaphoreSignal::NumbersToFollow:
			return {{{90, 45, 0, 90, 90, 0}, default_semaphore_delay}};
			break;
		case SemaphoreSignal::Rest:
			return toSemaphoreAnimation(' ');
			break;
		case SemaphoreSignal::Cancel:
			return {{{-90, 45, 0, 90, 45, 0}, default_semaphore_delay}};
			break;
		default:
			return {{{0, 0, 0, 0, 0, 0}, 0}};
			break;
	}
}

void KHR_1::pose(const KHR_1::Pose & pose, int speed)
{
	left_s_pitch.write(pose.left_s_pitch_angle, speed, true);
	left_s_roll.write(pose.left_s_roll_angle, speed, true);
	left_elbow.write(pose.left_elbow_angle, speed, true);
	right_s_pitch.write(pose.right_s_pitch_angle, speed, true);
	right_s_roll.write(pose.right_s_roll_angle, speed, true);
	right_elbow.write(pose.right_elbow_angle, speed, true);
}

/* WIP
const KHR_1::Animation KHR_1::stringToSemaphoreAnimation(const std::string & s) const
{
	// Initialize the animation with the Attention signal
	Animation animation{toSemaphoreAnimation(SemaphoreSignal::Attention)};

	// Add animation for every char, plus extra animations for starting numbers or letters
	for (size_t i{0}; i < s.size() - 1; i++)
	{
		// Add signal for the current character
		Animation charSignal{toSemaphoreAnimation(s[i])};
		animation.insert(animation.end(), charSignal.begin(), charSignal.end());
		
		// Add a "Numbers to Follow" signal if the next character is a number
		if (std::isalpha(s[i]) && std::isdigit(s[i + 1]))
		{
			Animation numberSignal{toSemaphoreAnimation(SemaphoreSignal::NumbersToFollow)};
			animation.insert(animation.end(), numberSignal.begin(), numberSignal.end());
		}
		// Add a "Letters to Follow" signal if the next character is a letter
		else if (std::isdigit(s[i]) && std::isalpha(s[i + 1]))
		{
			Animation letterSignal{toSemaphoreAnimation(SemaphoreSignal::LettersToFollow)};
			animation.insert(animation.end(), letterSignal.begin(), letterSignal.end());
		}
	}

	// Add signal for the last character
	Animation lastCharSignal{toSemaphoreAnimation(s.back())};
	animation.insert(animation.end(), lastCharSignal.begin(), lastCharSignal.end());

	// Add "End of Message" or "Ready to Receive" signal
	Animation endSignal{toSemaphoreAnimation(SemaphoreSignal::ReadyToReceive)};
	animation.insert(animation.end(), endSignal.begin(), endSignal.end());

	return animation;
}
*/

void KHR_1::animate(const Animation & animation)
{
	for (auto & frame : animation)
	{
		/*
		Serial.print("Posing: ");
		Serial.print(frame.pose.left_s_pitch_angle);
		Serial.print(", ");
		Serial.print(frame.pose.left_s_roll_angle);
		Serial.print(", ");
		Serial.print(frame.pose.left_elbow_angle);
		Serial.print(", ");
		Serial.print(frame.pose.right_s_pitch_angle);
		Serial.print(", ");
		Serial.print(frame.pose.right_s_roll_angle);
		Serial.print(", ");
		Serial.print(frame.pose.right_elbow_angle);
		Serial.print("\nDelaying: ");
		Serial.print(frame.duration);
		Serial.print("\n");
		*/
		pose(frame.pose);
		delay(frame.duration);
	}
}
