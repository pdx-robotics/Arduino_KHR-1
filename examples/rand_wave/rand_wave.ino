#include <KHR_1.h>

void setup() {
  attach_KHR_1();
  randomSeed(analogRead(0));
}

void loop() {
  int randnumber = random(0,4);
  if(randnumber<2)
    left_wave();
  else
    right_wave();

}
