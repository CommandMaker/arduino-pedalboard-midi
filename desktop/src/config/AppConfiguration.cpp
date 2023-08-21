//
// Created by Command_maker on 19/08/2023.
//

#include "AppConfiguration.h"

#include <QCoreApplication>

#define CONFIG_PATH QCoreApplication::applicationDirPath() + "/config" + "/config.json"

using namespace std::filesystem;

AppConfiguration::AppConfiguration() : JSONManipulator(CONFIG_PATH) {
}

/**
 * Set the serial port to the config file
 */
void AppConfiguration::set_serial_port(const QString &serial_port) {
    set("serial.port", serial_port);
}

/**
 * Get the serial port used by the Arduino
 *
 * @return
 */
QString AppConfiguration::get_serial_port() {
    return has("serial.port") ? get("serial.port").toString() : nullptr;
}

/**
 * Get the MIDI port to send data on
 *
 * @return
 */
QString AppConfiguration::get_midi_port() {
    return has("midi.port") ? get("midi.port").toString() : nullptr;
}

/**
 * Set the latest MIDI port used in the config
 *
 * @param midi_port
 */
void AppConfiguration::set_midi_port(const QString &midi_port) {
    set("midi.port", midi_port);
}