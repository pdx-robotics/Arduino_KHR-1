// Use random number generator and wave arms
#include <KHR_1.h>

void setup()
{
  attach_KHR_1();
  randomSeed(analogRead(0));
}

void loop()
{
  int randnumber = random(0,6);
  
  if (randnumber<2)
    left_wave();
  else if (randnumber>1 && randnumber<5)
    right_wave();
  else 
    both_wave();
}
