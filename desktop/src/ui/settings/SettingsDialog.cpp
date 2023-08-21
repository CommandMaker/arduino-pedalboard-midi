//
// Created by Command_maker on 20/08/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingsDialog.h" resolved

#include <QMessageBox>
#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);

    setup_midi_choices_combo();
    qDebug() << m_config.get_json();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

/**
 * Setup MIDI combo box with MIDI ports
 */
void SettingsDialog::setup_midi_choices_combo() {
    ui->midi_port_combo->clear();
    ui->midi_port_combo->addItem("[Non connecté]");
    QString config_port = m_config.get_midi_port();

    try {
        unsigned int port_count = m_midi.getPortCount();

        for (int i = 1; i <= port_count; i++) {
            std::string port_name = m_midi.getPortName(i - 1);
            port_name = port_name.substr(0, port_name.size() - 2);
            ui->midi_port_combo->addItem(QString::fromStdString(port_name));

            if (config_port.toStdString() == port_name) {
                ui->midi_port_combo->setCurrentText(config_port);
            }
        }
    } catch (RtMidiError err) {
        QMessageBox::critical(nullptr, "Error",
                              "Error while scanning midi ports : " + QString::fromStdString(err.getMessage()));
    }

    connect(ui->midi_port_combo, &QComboBox::currentIndexChanged, this, [this](int index) {
        std::string port_name = m_midi.getPortName(index - 1);
        port_name = port_name.substr(0, port_name.size() - 2);
        m_config.set_midi_port(QString::fromStdString(port_name));
        qInfo() << "Selected MIDI port :" << ui->midi_port_combo->itemText(index) << "with port id :" << index;
    });
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

/**
 * When the user click the "Save" button
 */
void SettingsDialog::accept() {
    m_config.flush();
    QDialog::accept();
}