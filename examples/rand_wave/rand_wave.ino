// Use random number generator and wave arms
#include <StandardCplusplus.h>
#include <string>
#include <locale>
#include <KHR_1.h>

KHR_1 khr;

void setup() {
	// khr.attach();
	randomSeed(analogRead(0));
}

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
