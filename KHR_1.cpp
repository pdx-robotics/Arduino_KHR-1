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
   pwm.setPWM(L_H_ROLL ,0,MAP(95));
   pwm.setPWM(L_H_PITCH,0,MAP(20));
   pwm.setPWM(L_KNEE   ,0,MAP(0));
   pwm.setPWM(L_A_PITCH,0,MAP(115));
   pwm.setPWM(L_A_ROLL ,0,MAP(90));
   
   pwm.setPWM(R_H_ROLL ,0,MAP(90));
   pwm.setPWM(R_H_PITCH,0,MAP(160));
   pwm.setPWM(R_KNEE   ,0,MAP(180));
   pwm.setPWM(R_A_PITCH,0,MAP(65));
   pwm.setPWM(R_A_ROLL ,0,MAP(95));
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
KHR_1::Pose::Pose() :
	left_s_pitch_angle{0},
	left_s_roll_angle{0},
	left_elbow_angle{0},
	right_s_pitch_angle{0},
	right_s_roll_angle{0},
	right_elbow_angle{0}
{}

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

KHR_1::Frame::Frame() : pose{}, duration{0}
{}

KHR_1::Frame::Frame(const Pose & pose, int duration) : pose{pose}, duration{duration}
{}

// Check if string is valid, then semaphore each letter
bool KHR_1::semaphore(const std::string & s)
{
	for (auto ch : s)
	{
		if (!(std::isalnum(ch) || ch == ' '))
		{
			return false;
		}
	}
	animate(stringToSemaphoreAnimation(s));
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
			return {Frame(Pose(-90, 90, 0, -90, 45, 0))};
			break;
		case 'b':
		case '2':
			return {Frame(Pose(-90, 90, 0, 0, 0, 0))};
			break;
		case 'c':
		case '3':
			return {Frame(Pose(-90, 90, 0, 90, 45, 0))};
			break;
		case 'd':
		case '4':
			return {Frame(Pose(-90, 90, 0, 90, 90, 0))};
			break;
		case 'e':
		case '5':
			return {Frame(Pose(90, 45, 0, -90, 90, 0))};
			break;
		case 'f':
		case '6':
			return {Frame(Pose(0, 0, 0, -90, 90, 0))};
			break;
		case 'g':
		case '7':
			return {Frame(Pose(-90, 45, 0, -90, 90, 0))};
			break;
		case 'h':
		case '8':
			return
			{
				Frame(Pose(0, 90, 0, 0, 0, 0), 400),
				Frame(Pose(-45, 90, 45, 0, 0, 0)),
				Frame(Pose(0, 90, 0, 0, 0, 0), 300)
			};
			break;
		case 'i':
		case '9':
			return
			{
				Frame(Pose(0, 90, 0, 0, 0, 0), 400),
				Frame(Pose(-45, 90, 45, 90, 45, 0)),
				Frame(Pose(0, 90, 0, 0, 0, 0), 300)
			};
			break;
		case 'j':
			return {Frame(Pose(0, 0, 0, 90, 90, 0))};
			break;
		case 'k':
		case '0':
			return {Frame(Pose(90, 90, 0, -90, 45, 0))};
			break;
		case 'l':
			return {Frame(Pose(90, 45, 0, -90, 45, 0))};
			break;
		case 'm':
			return {Frame(Pose(0, 0, 0, -90, 45, 0))};
			break;
		case 'n':
			return {Frame(Pose(-90, 45, 0, -90, 45, 0))};
			break;
		case 'o':
			return
			{
				Frame(Pose(0, 90, 0, 0, 0, 0), 400),
				Frame(Pose(45, 90, 45, 0, 0, 0)),
				Frame(Pose(0, 90, 0, 0, 0, 0), 300)
			};
			break;
		case 'p':
			return {Frame(Pose(90, 90, 0, 0, 0, 0))};
			break;
		case 'q':
			return {Frame(Pose(90, 45, 0, 0, 0, 0))};
			break;
		case 'r':
			return {Frame(Pose(0, 0, 0, 0, 0, 0))};
			break;
		case 's':
			return {Frame(Pose(-90, 45, 0, 0, 0, 0))};
			break;
		case 't':
			return {Frame(Pose(90, 90, 0, 90, 45, 0))};
			break;
		case 'u':
			return {Frame(Pose(90, 45, 0, 90, 45, 0))};
			break;
		case 'v':
			return {Frame(Pose(-90, 45, 0, 90, 90, 0))};
			break;
		case 'w':
			return
			{
				Frame(Pose(0, 0, 0, 0, 90, 0), 400),
				Frame(Pose(0, 0, 0, 45, 90, 45)),
				Frame(Pose(0, 0, 0, 0, 90, 0), 300)
			};
			break;
		case 'x':
			return
			{
				Frame(Pose(-90, 45, 0, 0, 90, 0), 400),
				Frame(Pose(-90, 45, 0, 45, 90, 45)),
				Frame(Pose(-90, 45, 0, 0, 90, 0), 300)
			};
			break;
		case 'y':
			return {Frame(Pose(0, 0, 0, 90, 45, 0))};
			break;
		case 'z':
			return
			{
				Frame(Pose(0, 0, 0, 0, 90, 0), 400),
				Frame(Pose(0, 0, 0, -45, 90, 45)),
				Frame(Pose(0, 0, 0, 0, 90, 0), 300)
			};
			break;
		case ' ':
			return {Frame(Pose(-90, 90, 0, -90, 90, 0))};
			break;
		default:
			return {Frame(Pose(0, 0, 0, 0, 0, 0))};
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
				Frame(Pose(90, 45, 0, 90, 45, 0)),
				Frame(Pose(-90, 45, 0, -90, 45, 0)),
				Frame(Pose(90, 45, 0, 90, 45, 0)),
				Frame(Pose(-90, 45, 0, -90, 45, 0)),
				Frame(Pose(90, 45, 0, 90, 45, 0)),
				Frame(Pose(-90, 45, 0, -90, 45, 0))
			};
			break;
		case SemaphoreSignal::ReadyToReceive:
			return
			{
				Frame(Pose(90, 90, 0, 90, 90, 0)),
				Frame(Pose(-90, 90, 0, -90, 90, 0))
			};
			break;
		case SemaphoreSignal::LettersToFollow:
			return toSemaphoreAnimation('j');
			break;
		case SemaphoreSignal::NumbersToFollow:
			return {Frame(Pose(90, 45, 0, 90, 90, 0))};
			break;
		case SemaphoreSignal::Rest:
			return toSemaphoreAnimation(' ');
			break;
		case SemaphoreSignal::Cancel:
			return {Frame(Pose(-90, 45, 0, 90, 45, 0))};
			break;
		default:
			return {Frame(Pose(0, 0, 0, 0, 0, 0))};
			break;
	}
}

void KHR_1::pose(const KHR_1::Pose & pose, int speed)
{
    pwm.setPWM(L_S_PITCH,0,MAP(pose.left_s_pitch_angle));
    pwm.setPWM(L_S_ROLL,0,MAP(pose.left_s_roll_angle));
    pwm.setPWM(L_ELBOW,0,MAP(pose.left_elbow_angle));
    pwm.setPWM(R_S_PITCH,0,MAP(pose.right_s_pitch_angle));
    pwm.setPWM(R_S_ROLL,0,MAP(pose.right_s_roll_angle));
    pwm.setPWM(R_ELBOW,0,MAP(pose.right_elbow_angle));
}

// WIP
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

void KHR_1::animate(const Animation & animation)
{
	for (auto & frame : animation)
	{
		pose(frame.pose);
		delay(frame.duration);
	}
}