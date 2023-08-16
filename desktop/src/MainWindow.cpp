#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup_file_menu();

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup_file_menu() {
    connect(ui->action_quit, &QAction::triggered, this, []() { QApplication::quit(); });
}