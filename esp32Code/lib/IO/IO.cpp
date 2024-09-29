#include "IO.h"

void waitForKeyPress()
{
    Serial.print("Press any key to continue");
    int i = 0;
    while (!Serial.available())
    {
        delay(100);
        if (i++ % 10 == 0)
        {
            Serial.print(".");
        }
    }
    Serial.println();

    Serial.read();

    while (Serial.available())
    {
        Serial.read();
    }
}