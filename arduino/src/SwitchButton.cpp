//
// Created by Command_maker on 15/08/2023.
//

#include <Arduino.h>

#include "SwitchButton.h"

SwitchButton::SwitchButton(uint8_t pin, uint8_t button_id)
    : m_pin(pin), m_prev_state(0), m_button_id(button_id) {
}

void SwitchButton::setup() const {
    pinMode(m_pin, INPUT);
}

void SwitchButton::loop() {
    uint8_t state = digitalRead(m_pin);

    if (state != m_prev_state) {
        Serial.print(m_button_id);
        Serial.print(',');
        Serial.print(state);
    }

    m_prev_state = state;
}

uint8_t SwitchButton::get_button_id() const { return m_button_id; }

uint8_t SwitchButton::get_button_state() const { return m_prev_state; }