#include <StandardCplusplus.h>
#include <string>
#include <vector>
#include <cctype>
#include <KHR_1.h>

KHR_1 khr;

void setup() {
	khr.attach();
}

void loop() {
	khr.semaphore("abcdefghijklmn");
}
