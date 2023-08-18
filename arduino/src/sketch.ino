#include <Arduino.h>
#include "SwitchButton.h"

SwitchButton button1(2, 1);
SwitchButton button2(3, 2);

SwitchButton *buttons[2] = {&button1, &button2};

void setup() {
    Serial.begin(115200);

    button1.setup();
    button2.setup();
}

void loop() {
    button1.loop();
    button2.loop();

    if (Serial.available() > 0) {
        String data = Serial.readString();
        data.trim();

        if (data == F("buttons_state")) {
            Serial.print(F("buttons_state:"));

            for (const SwitchButton *b: buttons) {
                Serial.print((String) b->get_button_id() + "," + (String) b->get_button_state() + "/");
            }
        }
    }

    delay(30);
}
