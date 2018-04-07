/* 
 *  Test and observe different speed values for 
 *  VarSpeedServo's write function using a single servo
 *  
 *  Note: 0 will default to full speed.
 */
#include <VarSpeedServo.h>
VarSpeedServo myservo; 
int khr_servo = 2;

void setup() {
  Serial.begin(9600);
  myservo.attach(khr_servo);
}

void loop() {
  int s; // Speed value for write function

  // Increment speed in intervals of 10
  for(int i = 0;i<15;i++)
  {
    s = i*10;
    Serial.print(s,DEC);
    Serial.print("\n");
    myservo.write(0,s,true); 
    myservo.write(180,s,true);
    delay(2000);
  }
}
