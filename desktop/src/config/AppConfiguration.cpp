//
// Created by Command_maker on 19/08/2023.
//

#include "AppConfiguration.h"

#include <filesystem>

#define CONFIG_PATH current_path() / "config" / "config.json"

using namespace std::filesystem;

AppConfiguration::AppConfiguration()
        : m_json(QString::fromStdString((CONFIG_PATH).string())) {
}

/**
 * Write stored config to the file
 */
void AppConfiguration::flush() const {
    QFile f = QFile(QString::fromStdString((CONFIG_PATH).string()));
    if (!f.exists()) return;
    f.open(QIODevice::ReadWrite | QIODevice::Text);
    f.resize(0);

    f.write(m_json.get_json().c_str());
    f.close();
}

/**
 * Set the serial port to the config file
 */
void AppConfiguration::set_serial_port(const QString &serial_port) {
    m_json.set("serial.port", serial_port);
    flush();
}

/**
 * Get the serial port used by the Arduino
 *
 * @return
 */
QString AppConfiguration::get_serial_port() {
    return m_json.has("serial.port") ? m_json.get("serial.port").toString() : nullptr;
}

/**
 * Get the MIDI port to send data on
 *
 * @return
 */
QString AppConfiguration::get_midi_port() {
    return m_json.has("midi.port") ? m_json.get("midi.port").toString() : nullptr;
}

/**
 * Set the latest MIDI port used in the config
 *
 * @param midi_port
 */
void AppConfiguration::set_midi_port(const QString &midi_port) {
    m_json.set("midi.port", midi_port);
    flush();
}