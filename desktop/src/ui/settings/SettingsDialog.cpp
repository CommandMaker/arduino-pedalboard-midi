//
// Created by Command_maker on 20/08/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingsDialog.h" resolved

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

#include <QMessageBox>
#include <QSerialPortInfo>
#include <regex>

SettingsDialog::SettingsDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);

    setup_midi_choices_combo();
    setup_serial_choices_combo();

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
        if (index != 0) {
            std::string port_name = m_midi.getPortName(index - 1);
            port_name = port_name.substr(0, port_name.size() - 2);
            m_config.set_midi_port(QString::fromStdString(port_name));
            qInfo() << "Selected MIDI port :" << ui->midi_port_combo->itemText(index) << "with port id :" << index;
        }
    });
}

/**
 * Setup Serial ports combo box with available serial ports
 */
void SettingsDialog::setup_serial_choices_combo() {
    QList available_ports = QSerialPortInfo::availablePorts();
    QString config_port = m_config.get_serial_port();

    for (unsigned int i = 1; const QSerialPortInfo &port: available_ports) {
        ui->serial_port_combo->addItem(port.description() + " (" + port.portName() + ")");

        if (port.description() == config_port) {
            ui->serial_port_combo->setCurrentIndex(i);
        }
    }

    connect(ui->serial_port_combo, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        const std::string &const_string = text.toStdString();
        std::smatch match;

        if (regex_search(const_string.begin(), const_string.end(), match, std::regex(R"(\(([^\(]+)\)$)"))) {
            QSerialPortInfo info(match[1].str().c_str());
            m_config.set_serial_port(info.description());
            qInfo() << "Selected serial port" << match[1].str() << "with device" << info.description();
        }
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