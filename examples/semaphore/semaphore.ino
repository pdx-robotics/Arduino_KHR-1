#include <StandardCplusplus.h>
#include <KHR_1.h>

KHR_1 khr;

void setup() {
	khr.attach();
  Serial.begin(9600);
}

void loop() {
	khr.semaphore("abcdefghijklmnopqrstuvwxyz");
}
