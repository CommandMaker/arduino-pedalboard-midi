#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "communication/SerialCommunication.h"
#include "communication/MIDICommunication.h"

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
    int m_selected_midi_port;

    void setup_file_menu();

    void setup_midi_choices_combo();

    /*
     * Slots
     */
    void serial_port_checkbox_change(bool checked);

    void handle_button_change(int button_id, int button_state);
};
#endif // MAINWINDOW_H
