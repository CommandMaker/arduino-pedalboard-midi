#include <Arduino.h>
#include "SwitchButton.h"

SwitchButton button1(2, 1);
SwitchButton button2(3, 2);

void setup() {
    Serial.begin(115200);

    button1.setup();
    button2.setup();
}

void loop() {
    button1.loop();
    button2.loop();

    delay(10);
}
