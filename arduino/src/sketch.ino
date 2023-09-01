#include <Arduino.h>
#include "SwitchButton.h"

SwitchButton button1(2, 1);
SwitchButton button2(3, 2);
SwitchButton button3(4, 3);
SwitchButton button4(5, 4);
SwitchButton button5(6, 5);
SwitchButton button6(7, 6);
SwitchButton button7(8, 7);
SwitchButton button8(9, 8);
SwitchButton button9(10, 9);
SwitchButton button10(11, 10);

SwitchButton *buttons[10] = {&button1, &button2, &button3, &button4, &button5, &button6, &button7, &button8, &button9,
                             &button10};

void setup() {
    Serial.begin(9600);

    for (const SwitchButton *button: buttons) {
        button->setup();
    }
}

void loop() {
    for (SwitchButton *button: buttons) {
        button->loop();
    }

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
