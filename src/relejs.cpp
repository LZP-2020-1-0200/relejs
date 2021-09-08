#include "relejs.h"

Relejs::Relejs(/* args */)
{
    pinMode(RELEJS, OUTPUT);
}

Relejs::~Relejs()
{
}

void Relejs::on(void)
{
    digitalWrite(RELEJS, HIGH); // turn the LED on (HIGH is the voltage level)
}
void Relejs::off(void)
{
    digitalWrite(RELEJS, LOW); // turn the LED off by making the voltage LOW
}

Relejs relejs;