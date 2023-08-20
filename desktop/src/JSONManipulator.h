//
// Created by Command_maker on 19/08/2023.
//

#ifndef MIDI_CONTROL_SOFTWARE_JSONMANIPULATOR_H
#define MIDI_CONTROL_SOFTWARE_JSONMANIPULATOR_H


#include <QJsonObject>
#include <QFile>

class JSONManipulator {
public:
    explicit JSONManipulator(const QString &path);

    QVariant get(const QString &key, const QVariant &defaultValue = QVariant()) const;

    void set(const QString &key, const QVariant &value);

    bool has(const QString &key) const;

    std::string get_json() const;

private:
    QJsonObject m_root;
};


#endif //MIDI_CONTROL_SOFTWARE_JSONMANIPULATOR_H
