#include <VarSpeedServo.h>

VarSpeedServo myservo;

void setup()
{
	Serial.begin(9600);
	myservo.attach(2);
}

void loop()
{
	int pos;
	while (Serial.available() > 0)
	{
		pos = Serial.parseInt();
		if (Serial.read() < '0' || Serial.read() > '9')
		{
			Serial.print("Writing: ");
			Serial.println(pos);
			myservo.write(pos);
		}
	}
}
