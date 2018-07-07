/*
  SweepTwoServos
  By Philip van Allen <philvanallen.com> for the VarSpeedServo.h library (October 2013)
  This example code is in the public domain
  
  Sweep two servos from 0-180, 180-0 in unison
  Uses the wait feature of the 2013 version of VarSpeedServo to start the first servo moving in the background
  and immediately starting a second servo moving and waiting for the second one to finish.
  
  Note that two servos will require more power than is available from the USB port - use an external power supply!
*/

#include <VarSpeedServo.h> 
 
VarSpeedServo myservo[12];
 
const int servoPin[] =  {2,3,4,5,6,7,8,9,10,11,12,13}; // the digital pin used for the second servo
 
void setup() { 
  for(int i=0; i <  12; ++i){ 
    myservo[i].attach(servoPin[i]);  // attaches the servo on pin 9 to the servo object
    myservo[i].write(0,255,false); // set the intial position of the servo, as fast as possible, run in background
  }
} 

void loop() {
  for(int i=0; i < 12; ++i){
    myservo[i].write(90,127,false);        // move the servo to 90, fast speed, run background
  }
  delay(5000);
  for(int i=0; i < 12; ++i){
    myservo[i].write(0,30,false);            // move the servo top
  }
  delay(5000);
} 
