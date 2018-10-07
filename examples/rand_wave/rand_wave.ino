/*
  Author:  VRS
  Date:    7/10/18
  Purpose: Use random number generator to wave arms.
*/
#include <KHR_1.h>

void setup() {
  attach_KHR_1();//Setup pins
  randomSeed(analogRead(0));
}

/*
*Randomly waves arms
*/
void loop() {
  int randnumber = random(0,6);
  
  if(randnumber<2)//Waves left arm if number is 0 or 1. 
    left_wave();
  
  //Waves right arm if number is 2,3, or 4. 
  else if(randnumber>1 && randnumber<5)
    right_wave();
  
  else//Waves both sides limbs if number is 5.  
    both_wave();

}
