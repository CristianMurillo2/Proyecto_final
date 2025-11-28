#include "pantallanivel2.h"
#include "ui_pantallanivel2.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QDebug>

pantallaNivel2::pantallaNivel2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pantallaNivel2)
    , m_bola(nullptr)
    , m_scene(nullptr)
    , cannon(nullptr)
    , base(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    this->showFullScreen();

    m_anguloGrados = ui->verticalSlider->value();
    ui->lblAngulo->setText(QString("%1°").arg(m_anguloGrados, 0, 'f', 0));

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &pantallaNivel2::verificarColisiones);

    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &pantallaNivel2::actualizarCronometro);

    sonidoDisparo = new QSoundEffect(this);
    sonidoDisparo->setSource(QUrl("qrc:/recursos/pistol-shot-233473.wav"));
    sonidoDisparo->setVolume(0.1f);

    iniciarNivel();
}

void pantallaNivel2::iniciarNivel(){

    m_scene->clear();
    m_bola = nullptr;
    cannon = nullptr;
    base = nullptr;
    obst.clear();
    tiempoRestante = 50;
    ui->lblTiempo->setText(QString::number(tiempoRestante));
    m_bola = nullptr;

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

    QPixmap pixMap3(":/recursos/bandera de francia.png");
    banderaF = new QGraphicsPixmapItem();
    m_scene -> addItem(banderaF);
    banderaF -> setPixmap(pixMap3);
    banderaF ->setScale(0.25);
    banderaF -> setPos(0,-205);

    QPixmap pixMap4(":/recursos/bandera britanica.png");
    banderaB = new QGraphicsPixmapItem();
    m_scene -> addItem(banderaB);
    banderaB -> setPixmap(pixMap4);
    banderaB ->setScale(0.25);
    banderaB -> setPos(1655,-835);

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

    if (timerColisiones->isActive()) timerColisiones->stop();
    timerColisiones->start(30);
    if (timerJuego->isActive()) timerJuego->stop();
    timerJuego->start(1000);

}
pantallaNivel2::~pantallaNivel2()
{
    if (timerColisiones) timerColisiones->stop();
    if (timerJuego->isActive()) timerJuego->stop();
    delete ui;
}

void pantallaNivel2::on_pushButton_clicked()
{
    this->close();
}

void pantallaNivel2::on_btnDisparar_clicked()
{
    if (m_bola != nullptr) {
        if (m_scene->items().contains(m_bola)) {
            m_scene->removeItem(m_bola);
            delete m_bola;
        }
        m_bola = nullptr;
    }
    if (sonidoDisparo) {
        sonidoDisparo->play();
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
    QTimer::singleShot(1000, this, [this, humo]() {
        if (m_scene && humo && m_scene->items().contains(humo)) {
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

void pantallaNivel2::reiniciarJuego()
{
    iniciarNivel();
}

void pantallaNivel2::actualizarCronometro()
{
    tiempoRestante--;
    ui->lblTiempo->setText(QString::number(tiempoRestante));

    if (tiempoRestante <= 0) {
        timerJuego->stop();
        if (timerColisiones->isActive()) timerColisiones->stop();

        qDebug() << ">>> GENERANDO GAME OVER (Dinámico) <<<";

        QRectF bounds = m_scene->sceneRect();
        QPointF centro = bounds.center();

        qDebug() << "Escena Rect:" << bounds << " Centro:" << centro;
        QGraphicsRectItem *fondoOscuro = new QGraphicsRectItem(bounds);

        QGraphicsSimpleTextItem *textoGO = new QGraphicsSimpleTextItem("GAME OVER");
        QFont fuente("Arial", 50, QFont::Bold);
        textoGO->setFont(fuente);
        textoGO->setBrush(QBrush(Qt::red));
        textoGO->setZValue(100);
        QRectF rectTexto = textoGO->boundingRect();
        qreal tx = centro.x() - (rectTexto.width() / 2);
        qreal ty = centro.y() - (rectTexto.height() / 2);

        textoGO->setPos(tx, ty);
        m_scene->addItem(textoGO);

        QTimer::singleShot(3000, this, &pantallaNivel2::close);
    }
}
