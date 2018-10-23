/*
 * Arduino_KHR-1.h - Library to control the Kondo KHR_1.
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
#include "Arduino_KHR-1.h"
#include <cctype>

KHR_1::KHR_1() {}

KHR_1::~KHR_1() {}

void KHR_1::init()
{
	Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
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

// Check if string is valid, then semaphore each letter
bool KHR_1::semaphore(const std::string & s, bool enableStartEndAnimations)
{
	// Check if string is valid
	for (auto ch : s)
	{
		if (!(std::isalnum(ch) || ch == ' '))
		{
			return false;
		}
	}

	if (enableStartEndAnimations)
	{
		// Begin signal
		Serial.print(F("\nSignaling: Attention\n"));
		animate(toSemaphoreAnimation(SemaphoreSignal::Attention));
	}

	// Signal if first character is a number
	if (std::isdigit(s[0]))
	{
		Serial.print(F("\nSignaling: Numbers to Follow\n"));
		animate(toSemaphoreAnimation(SemaphoreSignal::NumbersToFollow));
	}
	
	for (size_t i{0}; i < s.size() - 1; i++)
	{
		Serial.print(F("\nSignaling: "));
		Serial.print(s[i]);
		Serial.print(F("\n"));
		animate(toSemaphoreAnimation(s[i]));

		if (std::isalpha(s[i]) && std::isdigit(s[i + 1]))
		{
			Serial.print(F("\nSignaling: Numbers to Follow\n"));
			animate(toSemaphoreAnimation(SemaphoreSignal::NumbersToFollow));
		}
		else if (std::isdigit(s[i]) && std::isalpha(s[i + 1]))
		{
			Serial.print(F("\nSignaling: Letters to Follow\n"));
			animate(toSemaphoreAnimation(SemaphoreSignal::LettersToFollow));
		}

		// Signal if next character is the same as current one
		if (s[i] == s[i + 1])
		{
			Serial.print(F("\nSignaling: Between Same Letters\n"));
			animate(toSemaphoreAnimation(SemaphoreSignal::BetweenSameLetters));
		}
	}

	// Last character
	Serial.print(F("\nSignaling: "));
	Serial.print(s.back());
	Serial.print(F("\n"));
	animate(toSemaphoreAnimation(s.back()));

	if (enableStartEndAnimations)
	{
		// End signal
		Serial.print(F("\nSignaling: Ready to Receive\n"));
		animate(toSemaphoreAnimation(SemaphoreSignal::ReadyToReceive));
	}

	return true;
}

// const KHR_1::Pose KHR_1::toSemaphorePose(char ch) const
const KHR_1::Animation KHR_1::toSemaphoreAnimation(char signal) const
{
	switch (signal)
	{
		case 'A':
		case 'a':
		case '1':
			return {{{-90, 90, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'B':
		case 'b':
		case '2':
			return {{{-90, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'C':
		case 'c':
		case '3':
			return {{{-90, 90, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'D':
		case 'd':
		case '4':
			return {{{-90, 90, 0, 90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'E':
		case 'e':
		case '5':
			return {{{90, 45, 0, -90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'F':
		case 'f':
		case '6':
			return {{{0, 0, 0, -90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'G':
		case 'g':
		case '7':
			return {{{-90, 45, 0, -90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'H':
		case 'h':
		case '8':
			return
			{
				{{0, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{-45, 90, 45, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay},
				{{0, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 200}
			};
			break;
		case 'I':
		case 'i':
		case '9':
			return
			{
				{{0, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{-45, 90, 45, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay},
				{{0, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 200}
			};
			break;
		case 'J':
		case 'j':
			return {{{0, 0, 0, 90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'K':
		case 'k':
		case '0':
			return {{{90, 90, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'L':
		case 'l':
			return {{{90, 45, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'M':
		case 'm':
			return {{{0, 0, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'N':
		case 'n':
			return {{{-90, 45, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'O':
		case 'o':
			return
			{
				{{0, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{45, 90, 45, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay},
				{{0, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 200}
			};
			break;
		case 'P':
		case 'p':
			return {{{90, 90, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'Q':
		case 'q':
			return {{{90, 45, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'R':
		case 'r':
			return {{{0, 0, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'S':
		case 's':
			return {{{-90, 45, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'T':
		case 't':
			return {{{90, 90, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'U':
		case 'u':
			return {{{90, 45, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'V':
		case 'v':
			return {{{-90, 45, 0, 90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'W':
		case 'w':
			return
			{
				{{0, 0, 0, 0, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{0, 0, 0, 45, 90, 45, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay},
				{{0, 0, 0, 0, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 200}
			};
			break;
		case 'X':
		case 'x':
			return
			{
				{{-90, 45, 0, 0, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{-90, 45, 0, 45, 90, 45, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay},
				{{-90, 45, 0, 0, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 200}
			};
			break;
		case 'Y':
		case 'y':
			return {{{0, 0, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case 'Z':
		case 'z':
			return
			{
				{{0, 0, 0, 0, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{0, 0, 0, -45, 90, 45, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay},
				{{0, 0, 0, 0, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 200}
			};
			break;
		case ' ':
			return {{{-90, 90, 0, -90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		default:
			return {{{0, 0, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 0}};
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
				{{90, 45, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{-90, 45, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{90, 45, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{-90, 45, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{90, 45, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400},
				{{-90, 45, 0, -90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 400}
			};
			break;
		case SemaphoreSignal::ReadyToReceive:
			return
			{
				{{90, 90, 0, 90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 500},
				{{-90, 90, 0, -90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 500}
			};
			break;
		case SemaphoreSignal::LettersToFollow:
			return toSemaphoreAnimation('j');
			break;
		case SemaphoreSignal::NumbersToFollow:
			return {{{90, 45, 0, 90, 90, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case SemaphoreSignal::Rest:
			return toSemaphoreAnimation(' ');
			break;
		case SemaphoreSignal::Cancel:
			return {{{-90, 45, 0, 90, 45, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, default_semaphore_delay}};
			break;
		case SemaphoreSignal::BetweenSameLetters:
			return {{{0, 90, 45, 0, 90, 45, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 200}};
			break;
		default:
			return {{{0, 0, 0, 0, 0, 0, 2, 30, -65, 40, -5, 2, 30, -65, 40, -5}, 0}};
			break;
	}
}

// Tranlate the pose from standard to actual servo values, then move the servos
void KHR_1::pose(const KHR_1::Pose & pose)
{
	pwm.setPWM(L_S_PITCH, 0, MAP(pose.left_s_pitch_angle + 90));
	pwm.setPWM(L_S_ROLL, 0, MAP(- pose.left_s_roll_angle + 90));
	pwm.setPWM(L_ELBOW, 0, MAP(- pose.left_elbow_angle + 90));

	pwm.setPWM(R_S_PITCH, 0, MAP(- pose.right_s_pitch_angle + 90));
	pwm.setPWM(R_S_ROLL, 0, MAP(pose.right_s_roll_angle + 90));
	pwm.setPWM(R_ELBOW, 0, MAP(pose.right_elbow_angle + 90));
	
	pwm.setPWM(L_H_ROLL, 0, MAP(- pose.left_h_roll_angle + 90));
	pwm.setPWM(L_H_PITCH, 0, MAP(- pose.left_h_pitch_angle + 90));
	pwm.setPWM(L_KNEE, 0, MAP(pose.left_knee_angle + 90));
	pwm.setPWM(L_A_PITCH, 0, MAP(pose.left_a_pitch_angle + 90));
	pwm.setPWM(L_A_ROLL, 0, MAP(pose.left_a_roll_angle + 90));

	pwm.setPWM(R_H_ROLL, 0, MAP(pose.right_h_roll_angle + 90));
	pwm.setPWM(R_H_PITCH, 0, MAP(pose.right_h_pitch_angle + 90));
	pwm.setPWM(R_KNEE, 0, MAP(- pose.right_knee_angle + 90));
	pwm.setPWM(R_A_PITCH, 0, MAP(- pose.right_a_pitch_angle + 90));
	pwm.setPWM(R_A_ROLL, 0, MAP(- pose.right_a_roll_angle + 90));
}

void KHR_1::animate(const Animation & animation)
{
	for (auto & frame : animation)
	{
		Serial.print(F("Posing: "));
		Serial.print(static_cast<int>(frame.pose.left_s_pitch_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.left_s_roll_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.left_elbow_angle));
		Serial.print(F(", "));

		Serial.print(static_cast<int>(frame.pose.right_s_pitch_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.right_s_roll_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.right_elbow_angle));
		Serial.print(F(", "));
		
		Serial.print(static_cast<int>(frame.pose.left_h_roll_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.left_h_pitch_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.left_knee_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.left_a_pitch_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.left_a_roll_angle));
		Serial.print(F(", "));

		Serial.print(static_cast<int>(frame.pose.right_h_roll_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.right_h_pitch_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.right_knee_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.right_a_pitch_angle));
		Serial.print(F(", "));
		Serial.print(static_cast<int>(frame.pose.right_a_roll_angle));

		Serial.print(F("\nDelaying: "));
		Serial.print(frame.duration);
		Serial.print(F("\n"));

		pose(frame.pose);
		delay(frame.duration);
	}
}

void KHR_1::zeroPose()
{
	pose({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
}

long KHR_1::MAP(long d)
{
	return map(d, 0, 180, DMIN, DMAX);
}
