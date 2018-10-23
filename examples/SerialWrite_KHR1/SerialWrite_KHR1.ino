/* 
 * Write a value to a servo connected to the PCA9865 Servo Driver.
 * Specify the channel and the value you want to write to it
 * through the Serial Monitor.
 */
#include <Adafruit_PWMServoDriver.h>
#include <Arduino_KHR-1.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define FREQ 60

void setup()
{
	Serial.begin(9600);
    pwm.begin();
    pwm.setPWMFreq(FREQ);
    delay(10);
    Serial.println("Write to a servo with the PCA9865 Servo Driver");
    Serial.println("<channel> <position>");
}

void loop()
{
	unsigned int pos;
    int channel;
	while (Serial.available() > 0)
	{   
        channel = Serial.parseInt();
		pos = Serial.parseInt();
        if(Serial.read() < '0' || Serial.read() > '9')
        {
		    if (!(channel < 0 && channel > 15))
		    { 
		        Serial.print("   ");
			    Serial.print(channel);
			    Serial.print("         ");
			    Serial.println(pos);
                pwm.setPWM(channel,0,MAP(pos));
            }
        }
    }
}
