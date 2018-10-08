#include <StandardCplusplus.h>
#include <Arduino_KHR1.h>

KHR_1 khr;

void setup() {
  Serial.begin(9600);
	khr.init();
}

void loop() {
	khr.semaphore("abcdefghijklmnopqrstuvwxyz");
}
