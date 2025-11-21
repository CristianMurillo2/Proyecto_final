#include "pantallanivel1.h"
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QBrush>

PantallaNivel1::PantallaNivel1(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800, 600);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    crearEscenario();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, jugador, &PersonajeNivel1::actualizarFisica);
    gameTimer->start(16);
}

void PantallaNivel1::crearEscenario()
{
    scene->setSceneRect(0, 0, 800, 600);
    view->setBackgroundBrush(QBrush(QColorConstants::Svg::lightblue));

    jugador = new PersonajeNivel1();

    jugador->setVelocidadMax(8.0);
    jugador->setTamano(70,70);
    jugador->setImagen("C:\\Users\\crist\\OneDrive\\Escritorio\\proyecto final\\build-untitled25-Desktop_Qt_6_5_3_MinGW_64_bit-Debug\\imagenes_barco\\PNG\\Default size\\Ships\\barco.png");
    jugador->setPos(375, 450);
    jugador->setZValue(10);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);

    scene->addItem(jugador);
    jugador->setFocus();

}

