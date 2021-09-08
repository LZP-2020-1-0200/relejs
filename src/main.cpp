#include <Arduino.h>

#include "task.h"
void setup() {
  // put your setup code here, to run once:
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.begin(9600);

}

void loop() {

if (Serial.available())
  {
    task_addChar(Serial.read());
    return;
  }

}