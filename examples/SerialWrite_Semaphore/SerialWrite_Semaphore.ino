/*
 * Writes one character at a time to KHR-1.
 */
#include <KHR_1.h>
#include <iostream>

KHR_1 khr;
std::string c;
void setup() {
  khr.init();
  Serial.begin(9600);
  Serial.println("Provide a letter and KHR-1 will translate into Flag Sempahore.");
}

void loop() {

  if(Serial.available() > 0)
  {
    c = Serial.read();
    if(!khr.semaphore(c))
    {
      Serial.print("Invalid string.\n");
    }
    else
    {
      Serial.print("Performing\n");
    }
  }

}
