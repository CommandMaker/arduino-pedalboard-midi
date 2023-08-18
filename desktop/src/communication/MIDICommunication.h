//
// Created by Command_maker on 17/08/2023.
//

#ifndef MIDI_CONTROL_SOFTWARE_MIDICOMMUNICATION_H
#define MIDI_CONTROL_SOFTWARE_MIDICOMMUNICATION_H

#include <QString>
#include "RtMidi.h"

class MIDICommunication {
public:
    explicit MIDICommunication();

    ~MIDICommunication();

    bool open_midi_port(int port_id);

    void close_midi_port();

    void send_control_change(int channel, int value);

    void send_program_change(int program);

    QVector<QString> &get_available_ports();

private:
    RtMidiOut *m_midi;
};


#endif //MIDI_CONTROL_SOFTWARE_MIDICOMMUNICATION_H
