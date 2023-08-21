#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "settings/SettingsDialog.h"

#include <filesystem>
#include <fstream>
#include <QMessageBox>

using namespace std::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    create_config_file_if_needed();

    ui->setupUi(this);
    setup_file_menu();

    m_serial = new SerialCommunication;
    connect(m_serial, &SerialCommunication::button_changed_state, this, &MainWindow::handle_button_change);

    m_midi = new MIDICommunication;

    ui->button1_state->hide();
    ui->button2_state->hide();
    ui->button3_state->hide();
    ui->button4_state->hide();
    ui->button5_state->hide();
    ui->button6_state->hide();
    ui->button7_state->hide();
    ui->button8_state->hide();
    ui->button9_state->hide();
    ui->button10_state->hide();

    connect(ui->serial_port_enabled, &QCheckBox::clicked, this, &MainWindow::serial_port_checkbox_change);
}

MainWindow::~MainWindow()
{
    delete m_serial;
    delete m_midi;
    delete ui;
}

/**
 * Setup actions of the menu bar
 */
void MainWindow::setup_file_menu() {
    connect(ui->action_quit, &QAction::triggered, this, []() { QApplication::quit(); });
    connect(ui->action_settings, &QAction::triggered, this, [this]() {
        SettingsDialog settings(this);
        settings.setWindowFlags(Qt::Window);
        settings.setWindowModality(Qt::ApplicationModal);
        settings.exec();
        m_config.reload_file();
    });
}

/**
 * Handle when the serial port checkbox state is changing to open or close the serial port
 * @param checked
 */
void MainWindow::serial_port_checkbox_change(bool checked) {
    if (checked) {
        int port_id = m_midi->get_port_from_name(m_config.get("midi.port").toString());

        qDebug() << m_config.get("midi.port").toString();

        if (port_id == -1) {
            QMessageBox::critical(this, "Error", "Error when opening the MIDI connection : Port introuvable");

            ui->serial_port_enabled->setCheckState(Qt::Unchecked);
            m_serial->close_serial_communication();
            m_midi->close_midi_port();

            return;
        }

        if (m_serial->open_serial_communication("COM3", QSerialPort::Baud115200) &&
            m_midi->open_midi_port(port_id))
            return;
    }

    ui->serial_port_enabled->setCheckState(Qt::Unchecked);
    m_serial->close_serial_communication();
    m_midi->close_midi_port();
}

/**
* Handle when a button changes state on the pedalboard
*/
void MainWindow::handle_button_change(int button_id, int button_state) {
    qInfo() << "Button id :" << button_id << "/ Button state :" << button_state;

    switch (button_id) {
        case 1:
            button_state == 0 ? ui->button1_state->hide() : ui->button1_state->show();
            m_midi->send_control_change(ui->button1_channel->value(), button_state ? 0 : 127);
            break;
        case 2:
            button_state == 0 ? ui->button2_state->hide() : ui->button2_state->show();
            m_midi->send_control_change(ui->button2_channel->value(), button_state ? 0 : 127);
            break;
    }
}

/**
 * Create the configuration file if it doesn't exist
 */
void MainWindow::create_config_file_if_needed() {
    path config_path = current_path() / "config";

    if (!exists(config_path)) {
        create_directory(config_path);

        std::ofstream file(config_path / "config.json");
        file << "{}";
        file.close();
    }
}