#include "pantallanivel2.h"
#include "ui_pantallanivel2.h"



pantallaNivel2::pantallaNivel2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pantallaNivel2)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    this->showFullScreen();

    m_anguloGrados = ui->verticalSlider->value();
    ui->lblAngulo->setText(QString("%1°").arg(m_anguloGrados, 0, 'f', 0));

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    QImage imagen(":/recursos/fondo nivel-2.jpeg");
    QBrush fondo(imagen);
    m_scene->setBackgroundBrush(fondo);

    QPixmap pixMap(":/recursos/cannon2-2.png");
    cannon = new QGraphicsPixmapItem();
    m_scene -> addItem(cannon);
    cannon -> setPixmap(pixMap);
    cannon -> setScale(0.25);
    cannon -> setPos(30,-150);

    QPixmap pixMap2(":/recursos/base.png");
    base = new QGraphicsPixmapItem();
    m_scene -> addItem(base);
    base -> setPixmap(pixMap2);
    base -> setPos(1680,-715);

    QPixmap imagenOriginal(":/recursos/tienda de campana1.png");
    QPixmap imagenEscalada = imagenOriginal.scaled(100, 67, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    for (int i = 0; i < 4; ++i) {
        QGraphicsPixmapItem* tienda = new QGraphicsPixmapItem(imagenEscalada);
        tienda->setPos(1260 + (i * 150), -120);
        m_scene->addItem(tienda);
        obst.append(tienda);
    }

    for (int i = 0; i < 5; ++i) {
        QGraphicsPixmapItem* tienda = new QGraphicsPixmapItem(imagenEscalada);
        tienda->setPos(1710 , -203 - (i * 106));
        m_scene->addItem(tienda);
        obst.append(tienda);
    }



    int width = this->width();
    int height = this->height();
    m_scene->setSceneRect(0, -height, width, height);
    imagenTiendaNormal.load(":/recursos/tienda de campana1.png");
    imagenTiendaNormal = imagenTiendaNormal.scaled(100, 67, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imagenTiendaRota.load(":/recursos/tienda2.png");
    imagenTiendaRota = imagenTiendaRota.scaled(100, 67, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &pantallaNivel2::verificarColisiones);
    timerColisiones->start(30);

}

pantallaNivel2::~pantallaNivel2()
{
    if (m_bola) {
        delete m_bola;
    }
    delete ui;
}

void pantallaNivel2::on_pushButton_clicked()
{
    this->close();
}

void pantallaNivel2::on_btnDisparar_clicked()
{
    if (m_bola != nullptr) {
        m_scene->removeItem(m_bola);
        delete m_bola;
        m_bola = nullptr;
    }
    double velocidad_inicial = 35.0;
    double angulo_rad = m_anguloGrados * (M_PI / 180.0);
    m_bola = new CannonBall(140, 120, velocidad_inicial, angulo_rad, m_scene, this);
    m_scene->addItem(m_bola);
    ui->graphicsView->centerOn(m_bola);

    QPixmap pixMap1(":/recursos/humo.png");
    QGraphicsPixmapItem *humo = new QGraphicsPixmapItem();
    m_scene -> addItem(humo);
    humo -> setPixmap(pixMap1);
    humo -> setScale(0.25);
    humo -> setPos(120,-170);
    QTimer::singleShot(1000, [this, humo](){
        if(humo && m_scene) {
            m_scene->removeItem(humo);
            delete humo;
        }
    });

}

void pantallaNivel2::on_verticalSlider_valueChanged(int value)
{
    m_anguloGrados = static_cast<double>(value);
    ui->lblAngulo->setText(QString("%1°").arg(m_anguloGrados, 0, 'f', 0));
}

void pantallaNivel2::verificarColisiones()
{
    if (m_bola == nullptr) return;
    for(int i = obst.length() - 1; i >= 0; i--){
        QGraphicsItem* itemActual = obst.at(i);
        if(m_bola->collidesWithItem(itemActual)){
            QGraphicsPixmapItem* tienda = dynamic_cast<QGraphicsPixmapItem*>(itemActual);
            if(tienda){
                tienda->setPixmap(imagenTiendaRota);
            }
            obst.removeAt(i);
            m_scene->removeItem(m_bola);
            delete m_bola;
            m_bola = nullptr;
            if (obst.isEmpty()) {
               this-> close();
            }
            return;
        }
    }
}
