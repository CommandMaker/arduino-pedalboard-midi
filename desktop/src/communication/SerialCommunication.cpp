//
// Created by Command_maker on 16/08/2023.
//

#include "SerialCommunication.h"

#include <QMessageBox>
#include "RtMidi.h"

SerialCommunication::SerialCommunication() {
    m_serial = new QSerialPort();

    connect(m_serial, &QSerialPort::readyRead, this, &SerialCommunication::data_received);
}

SerialCommunication::~SerialCommunication() {
    close_serial_communication();
    delete m_serial;
}

/**
 * Open the serial port connection if closed
 *
 * @param baud_rate
 * @param data_bits
 * @param parity
 * @param stop_bits
 * @param flow_control
 * @param open_mode
 * @param parent
 * @return
 */
bool SerialCommunication::open_serial_communication(
        const QString &port,
        qint32 baud_rate,
        QSerialPort::DataBits data_bits,
        QSerialPort::Parity parity,
        QSerialPort::StopBits stop_bits,
        QSerialPort::FlowControl flow_control,
        QIODevice::OpenModeFlag open_mode,
        QWidget *parent) {
    m_serial->setPortName(port);

    if (!m_serial->isOpen()) {
        m_serial->setBaudRate(baud_rate);
        m_serial->setDataBits(data_bits);
        m_serial->setParity(parity);
        m_serial->setStopBits(stop_bits);
        m_serial->setFlowControl(flow_control);

        bool open = m_serial->open(open_mode);

        if (!open) {
            QMessageBox::critical(parent, "Error", "Error while opening serial port : " + m_serial->errorString());
        }

        if (open) {
            ask_buttons_state();
        }

        return open;
    }

    return false;
}

/**
 * Close the serial connection if open
 */
void SerialCommunication::close_serial_communication() {
    if (m_serial->isOpen()) m_serial->close();
}

/**
 * Callback triggered when data are available on serial port
 */
void SerialCommunication::data_received() {
    QString data = QString(m_serial->readAll());

    if (data.startsWith("buttons_state")) {
        QStringList buttons_state = data.sliced(0, data.size() - 1).split(':')[1].split('/');

        for (const QString &b: buttons_state) {
            QStringList a = b.split(',');
            if (a.size() != 2) return;
            emit button_changed_state(a.at(0).toInt(), a.at(1).toInt());
        }
    } else {
        auto a = data.split(',');
        if (a.size() != 2) return;

        emit button_changed_state(a.at(0).toInt(), a.at(1).toInt());
    }
}

void SerialCommunication::ask_buttons_state() {
    m_serial->write(QString("buttons_state").toLatin1());
}