/*
  Author:  Geoffrey Olson Jr.
  Date:    7/7/18
  Purpose: This is a test to see if the VarSpeedServo library can handle more than 8 servos.
           Documentation states VarSpeedServo can only support a maximum of 8 servos.
*/
#include <VarSpeedServo.h> 

VarSpeedServo servo[12];

const int servoPin[] = {2,3,4,5,6,7,8,9,10,11,12,13}; // the digital pins used for the servos
const int angleInc = 10; //set the angle increments

void setup() { 
  for(int i=0; i <  12; ++i){ 
    servo[i].attach(servoPin[i]); // attaches the pins to the servo objects
    servo[i].write(0,255,false); // set the intial position of the servo, as fast as possible, run in background
  }
} 

void loop() {
  for(int i=0; i < 12; ++i){
    servo[i].write((angleInc*(i+1)),127,false); // move each servo angleInc degrees further then the last, fast speed, run background
  }
  delay(5000);
  for(int i=0; i < 12; ++i){
    servo[i].write(0,30,false); // move the servo top
  }
  delay(5000);
}
