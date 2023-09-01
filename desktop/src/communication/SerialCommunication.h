//
// Created by Command_maker on 16/08/2023.
//

#ifndef MIDI_CONTROL_SOFTWARE_SERIALCOMMUNICATION_H
#define MIDI_CONTROL_SOFTWARE_SERIALCOMMUNICATION_H

#include <QObject>
#include <QSerialPort>

class SerialCommunication : public QObject {
Q_OBJECT

public:
    explicit SerialCommunication();

    ~SerialCommunication();

    bool open_serial_communication(
            const QString &port,
            qint32 baud_rate,
            QSerialPort::DataBits data_bits = QSerialPort::Data8,
            QSerialPort::Parity parity = QSerialPort::NoParity,
            QSerialPort::StopBits stop_bits = QSerialPort::OneStop,
            QSerialPort::FlowControl flow_control = QSerialPort::NoFlowControl,
            QIODevice::OpenModeFlag open_mode = QIODevice::ReadWrite,
            QWidget *parent = nullptr);

    void close_serial_communication();

    void ask_buttons_state();

    QString get_port_from_device_name(const QString &device_name) const;

signals:

    void init_buttons_state_gathered(QStringList buttons);

    void button_changed_state(int button_id, int button_value);

private:
    QSerialPort *m_serial;

    void data_received();
};


#endif //MIDI_CONTROL_SOFTWARE_SERIALCOMMUNICATION_H
