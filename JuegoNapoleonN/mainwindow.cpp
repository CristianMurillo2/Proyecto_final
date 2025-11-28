#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>
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
    this->hide();
    PantallaNivel1 *nivel1 = new PantallaNivel1(this);
    connect(nivel1, &QDialog::finished, this, [this]() {
        this->show();
        if (m_gifAnimacion) m_gifAnimacion->start();
        centrarVentana();
    });
    nivel1->show();
}

void MainWindow::on_btnNivel2_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();
    this->hide();

    pantalla2 = new pantallaNivel2(this);

    connect(pantalla2, &QDialog::finished, this, [this](){
        this->show();
        if(m_gifAnimacion) m_gifAnimacion->start();
    });

    pantalla2->show();
}

void MainWindow::on_btnNivel3_clicked()
{
    if (m_gifAnimacion) m_gifAnimacion->stop();
    this->hide();

    pantalla3 = new PantallaNivel3(this);

    connect(pantalla3, &QDialog::finished, this, [this](){
        this->show();
        if(m_gifAnimacion) m_gifAnimacion->start();
    });

    pantalla3->show();
}

void MainWindow::centrarVentana()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}
