#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QUrl>
#include "pantallanivel1.h"
#include "pantallanivel2.h"
#include "pantallanivel3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_gifAnimacion = new QMovie(":/recursos/PortadaNapoleon.gif");

    m_fondoLabel = new QLabel(this);
    m_fondoLabel->setScaledContents(true);
    m_fondoLabel->resize(this->size());
    m_fondoLabel->lower();

    m_fondoLabel->setMovie(m_gifAnimacion);
    m_gifAnimacion->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (m_fondoLabel) {
        m_fondoLabel->resize(this->size());
    }
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_btnNivel1_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();

    hide();

    pantalla1 = new pantallaNivel1(this);
    pantalla1->setAttribute(Qt::WA_DeleteOnClose);
    pantalla1->show();

    connect(pantalla1, &QDialog::finished, this, [this](){
        this->show();
        if (m_gifAnimacion) m_gifAnimacion->start();
    });
}


void MainWindow::on_btnNivel2_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();

    hide();

    pantalla2 = new pantallaNivel2(this);
    pantalla2->setAttribute(Qt::WA_DeleteOnClose);
    pantalla2->show();

    connect(pantalla2, &QDialog::finished, this, [this](){
        this->show();
        if (m_gifAnimacion) m_gifAnimacion->start();
    });
}

void MainWindow::on_btnNivel3_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();

    hide();

    pantalla3 = new pantallaNivel3(this);
    pantalla3->setAttribute(Qt::WA_DeleteOnClose);
    pantalla3->show();

    connect(pantalla3, &QDialog::finished, this, [this](){
        this->show();
        if (m_gifAnimacion) m_gifAnimacion->start();
    });
}

