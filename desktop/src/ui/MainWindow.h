#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>

#include "../communication/SerialCommunication.h"
#include "../communication/MIDICommunication.h"
#include "../config/AppConfiguration.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    SerialCommunication *m_serial;
    MIDICommunication *m_midi;
    AppConfiguration m_config;
    int m_selected_midi_port;

    QList<QLabel *> m_buttons_state_indicator;
    QList<QSpinBox *> m_buttons_channels;

    void setup_file_menu();

    void create_config_file_if_needed();

    /*
     * Slots
     */
    void serial_port_checkbox_change(bool checked);
    void handle_button_change(int button_id, int button_state);
};
#endif // MAINWINDOW_H
