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
#include "Arduino.h"
#include "KHR_1.h"
#include <cctype>

KHR_1::KHR_1()
{
}

KHR_1::~KHR_1()
{
}

void KHR_1::init()
{
    pwm.begin();
    pwm.setPWMFreq(FREQ);
    delay(10);
}

void KHR_1::stand()
{
	pwm.setPWM(L_H_ROLL, 0, MAP(95));
	pwm.setPWM(L_H_PITCH, 0, MAP(20));
	pwm.setPWM(L_KNEE, 0, MAP(0));
	pwm.setPWM(L_A_PITCH, 0, MAP(115));
	pwm.setPWM(L_A_ROLL, 0, MAP(90));

	pwm.setPWM(R_H_ROLL, 0, MAP(90));
	pwm.setPWM(R_H_PITCH, 0, MAP(160));
	pwm.setPWM(R_KNEE, 0, MAP(180));
	pwm.setPWM(R_A_PITCH, 0, MAP(65));
	pwm.setPWM(R_A_ROLL, 0, MAP(95));
}

/*
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
*/

// WIP
KHR_1::Pose::Pose(int left_s_pitch_angle, int left_s_roll_angle, int left_elbow_angle,
	int left_h_roll_angle, int left_h_pitch_angle, int left_knee_angle,
	int left_a_pitch_angle, int left_a_roll_angle,
	int right_s_pitch_angle, int right_s_roll_angle, int right_elbow_angle,
	int right_h_roll_angle, int right_h_pitch_angle, int right_knee_angle,
	int right_a_pitch_angle, int right_a_roll_angle) :
		left_s_pitch_angle{left_s_pitch_angle + 90},
		left_s_roll_angle{- left_s_roll_angle + 90},
		left_elbow_angle{- left_elbow_angle + 90},
		left_h_roll_angle{left_h_roll_angle}, // Needs conversion
		left_h_pitch_angle{left_h_pitch_angle}, // Needs conversion
		left_knee_angle{left_knee_angle}, // Needs conversion
		left_a_pitch_angle{left_a_pitch_angle}, // Needs conversion
		left_a_roll_angle{left_a_roll_angle}, // Needs conversion
		right_s_pitch_angle{- right_s_pitch_angle + 90},
		right_s_roll_angle{right_s_roll_angle + 90},
		right_elbow_angle{right_elbow_angle + 90},
		right_h_roll_angle{right_h_roll_angle}, // Needs conversion
		right_h_pitch_angle{right_h_pitch_angle}, // Needs conversion
		right_knee_angle{right_knee_angle}, // Needs conversion
		right_a_pitch_angle{right_a_pitch_angle}, // Needs conversion
		right_a_roll_angle{right_a_roll_angle} // Needs conversion
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
	// WIP Need legs coordinates
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
	pwm.setPWM(L_S_PITCH, 0, MAP(pose.left_s_pitch_angle));
	pwm.setPWM(L_S_ROLL, 0, MAP(pose.left_s_roll_angle));
	pwm.setPWM(L_ELBOW, 0, MAP(pose.left_elbow_angle));
	pwm.setPWM(R_S_PITCH, 0, MAP(pose.right_s_pitch_angle));
	pwm.setPWM(R_S_ROLL, 0, MAP(pose.right_s_roll_angle));
	pwm.setPWM(R_ELBOW, 0, MAP(pose.right_elbow_angle));
}

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
