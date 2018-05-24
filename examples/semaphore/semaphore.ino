#include <StandardCplusplus.h>
#include <string>
#include <locale>
#include <KHR_1.h>

KHR_1 khr;

void setup() {
}

void loop() {
	khr.semaphore("ab");
}
