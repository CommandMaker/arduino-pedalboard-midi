//
// Created by Command_maker on 17/08/2023.
//

#include "MIDICommunication.h"

#include "RtMidi.h"
#include <QMessageBox>

MIDICommunication::MIDICommunication() {
    m_midi = new RtMidiOut();
}

MIDICommunication::~MIDICommunication() {
    m_midi->closePort();
    delete m_midi;
}

/**
 * List all available MIDI ports as a QMap
 */
QVector<QString> &MIDICommunication::get_available_ports() {
    static QVector<QString> ports;

    try {
        unsigned int port_count = m_midi->getPortCount();

        for (int i = 0; i < port_count; i++) {
            std::string port_name = m_midi->getPortName(i);
            port_name = port_name.substr(0, port_name.size() - 2);
            ports.push_back(QString::fromStdString(port_name));
        }
    } catch (RtMidiError err) {
        QMessageBox::critical(nullptr, "Error",
                              "Error while scanning midi ports : " + QString::fromStdString(err.getMessage()));
    }

    return ports;
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
