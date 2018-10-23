/*
  Author:  Geoffrey Olson Jr.
  Date:    7/10/18
  Purpose: This is a test to see if the VarSpeedServo library can handle more than 8 servos.
           Documentation states VarSpeedServo can only support a maximum of 8 servos.          
  UPDATE:  Found we can operate up to 12 servos with the nano or uno. On line 122 of VarSpeedServo.h
           there is a macro setting the maximum number of servos per timer to 12. Changing the macro
           value we were able to operate all 17 servos needed for the KHR-1. We've yet to find any side
           effects from adding this many servos.    
*/

#include <VarSpeedServo.h> 

const int SERVO_CNT = 17;
VarSpeedServo servo[SERVO_CNT];

const int servoPin[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18}; // the digital pins and analog pins used for the servos
const int ANGLE_INC = 5; //set the angle increments

void setup() {
  for(int i=0; i < SERVO_CNT; ++i){ 
    servo[i].attach(servoPin[i]); // attaches the pins to the servo objects
  }
} 

void loop() {
  for(int i=0; i < SERVO_CNT; ++i){
    servo[i].write(ANGLE_INC*(i+1), 30,false); // move each servo angleInc degrees further then the last, at a reduced speed, run background
  }
  delay(5000);
  for(int i=0; i < SERVO_CNT; ++i){
    servo[i].write(0,45,false); // move the servos top
  }
  delay(5000);
}
