#include "pantallanivel2.h"
#include "ui_pantallanivel2.h"
#include <QPainter>
#define _USE_MATH_DEFINES
#include <cmath>

pantallaNivel2::pantallaNivel2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pantallaNivel2)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    m_scene->setSceneRect(0, -600, 800, 600);

    ui->graphicsView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

pantallaNivel2::~pantallaNivel2()
{
    delete ui;
}

void pantallaNivel2::on_pushButton_clicked()
{
    this->close();
}

void pantallaNivel2::on_btnDisparar_clicked()
{
    m_scene->clear();

    double velocidad_inicial = 20.0;
    double angulo_grados = 40.0;
    double angulo_rad = angulo_grados * (M_PI / 180.0);

    m_bola = new CannonBall(0, 0, velocidad_inicial, angulo_rad, m_scene, this);

    m_scene->addItem(m_bola);

    ui->graphicsView->centerOn(m_bola);
}
