#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PantallaNivel3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    PantallaNivel1 *nivel = new PantallaNivel1(this);
    setCentralWidget(nivel);
    resize(1280, 720);

    centrarVentana();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::centrarVentana()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}
