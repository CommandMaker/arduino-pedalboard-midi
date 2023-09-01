//
// Created by Command_maker on 20/08/2023.
//

#ifndef MIDI_CONTROL_SOFTWARE_SETTINGSDIALOG_H
#define MIDI_CONTROL_SOFTWARE_SETTINGSDIALOG_H

#include <QDialog>
#include "../../config/AppConfiguration.h"
#include "../../communication/MIDICommunication.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SettingsDialog; }
QT_END_NAMESPACE

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    ~SettingsDialog() override;

private:
    Ui::SettingsDialog *ui;
    AppConfiguration m_config;
    RtMidiOut m_midi;

    void accept() override;

    void setup_midi_choices_combo();

    void setup_serial_choices_combo();
};


#endif //MIDI_CONTROL_SOFTWARE_SETTINGSDIALOG_H
