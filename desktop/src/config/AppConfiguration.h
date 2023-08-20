//
// Created by Command_maker on 19/08/2023.
//

#ifndef MIDI_CONTROL_SOFTWARE_APPCONFIGURATION_H
#define MIDI_CONTROL_SOFTWARE_APPCONFIGURATION_H

#include "../JSONManipulator.h"

class AppConfiguration {
public:
    explicit AppConfiguration();

    /*
     * Setters
     */
    void set_serial_port(const QString &serial_port);

    void set_midi_port(const QString &midi_port);

    /*
     * Getters
     */
    QString get_serial_port();

    QString get_midi_port();

    void flush() const;

private:
    JSONManipulator m_json;
};


#endif //MIDI_CONTROL_SOFTWARE_APPCONFIGURATION_H
