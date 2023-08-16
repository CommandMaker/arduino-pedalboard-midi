//
// Created by Command_maker on 15/08/2023.
//

#pragma once

class SwitchButton {
public:
    explicit SwitchButton(uint8_t pin, uint8_t button_id);

    void setup() const;
    void loop();

private:
    uint8_t m_pin;
    uint8_t m_button_id;
    uint8_t m_prev_state;
};
