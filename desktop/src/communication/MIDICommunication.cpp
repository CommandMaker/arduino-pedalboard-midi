//
// Created by Command_maker on 17/08/2023.
//

#include "MIDICommunication.h"

#include <RtMidi.h>
#include <QMessageBox>

MIDICommunication::MIDICommunication() {
    m_midi = new RtMidiOut();
}

MIDICommunication::~MIDICommunication() {
    m_midi->closePort();
    delete m_midi;
}

/**
 * Get the port name from its id
 *
 * @param port_id
 * @return
 */
QString MIDICommunication::get_port_from_id(int port_id) {
    std::string port_name = m_midi->getPortName(port_id);
    port_name = port_name.substr(0, port_name.size() - 2);

    return QString::fromStdString(port_name);
}

/**
 * Get MIDI port id from its name
 *
 * @param port_name
 * @return
 */
int MIDICommunication::get_port_from_name(const QString &port_name) {
    const int ports = m_midi->getPortCount();

    for (int i = 0; i < ports; i++) {
        const std::string port = m_midi->getPortName(i);

        if (port.substr(0, port.size() - 2) == port_name.toStdString()) {
            return i;
        }
    }

    return -1;
}

/**
 * Open the selected MIDI port
 * @param port_id
 */
bool MIDICommunication::open_midi_port(int port_id) {
    try {
        m_midi->openPort(port_id);
        return true;
    } catch (RtMidiError err) {
        QMessageBox::critical(nullptr, "Error",
                              QString::fromStdString("Error while opening the MIDI port : " + err.getMessage()));
        return false;
    }
}

void MIDICommunication::close_midi_port() {
    m_midi->closePort();
}

/**
 * Send Control Change to the MIDI port
 *
 * @param channel
 * @param value
 */
void MIDICommunication::send_control_change(int channel, int value) {
    if (m_midi->isPortOpen()) {
        std::vector<unsigned char> message;
        message.push_back(176),
                message.push_back(channel);
        message.push_back(value);

        m_midi->sendMessage(&message);

        return;
    }

    QMessageBox::critical(nullptr, "Error", "You must open the MIDI port before sending message !");
}

/**
 * Send a Program Change to the MIDI port
 *
 * @param program
 */
void MIDICommunication::send_program_change(int program) {
    if (m_midi->isPortOpen()) {
        std::vector<unsigned char> message;
        message.push_back(192);
        message.push_back(program);

        m_midi->sendMessage(&message);

        return;
    }

    QMessageBox::critical(nullptr, "Error", "You must open the MIDI port before sending message !");
}
