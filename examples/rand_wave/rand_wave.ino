/*
  Author:  VRS
  Date:    7/10/18
  Purpose: Use random number generator to wave arms.
*/

#include <StandardCplusplus.h>
#include <string>
#include <locale>
#include <Arduino_KHR-1.h>

KHR_1 khr;

void setup() {
	khr.init();
	randomSeed(analogRead(0));
}

/*
*Randomly waves arms
*/
void loop() {
	int randnumber = random(0, 6);

	if (randnumber < 2) {
		khr.left_wave();
	}
	else if (randnumber > 1 && randnumber < 5) {
		khr.right_wave();
	}
	else {
		khr.both_wave();
	}
}
