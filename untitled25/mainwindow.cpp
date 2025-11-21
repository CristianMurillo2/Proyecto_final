#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nivel1 = new PantallaNivel1(this);
    setCentralWidget(nivel1);

    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
