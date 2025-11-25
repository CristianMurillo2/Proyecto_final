#include "PantallaNivel3.h"
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QBrush>

PantallaNivel3::PantallaNivel3(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setFixedSize(1280, 720);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    crearEscenario();

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, jugador, &PersonajeNivel3::actualizarMovimiento);
    gameTimer->start(16);
}

void PantallaNivel3::crearEscenario()
{
    int ancho = 1280;
    int alto = 720;
    scene->setSceneRect(0, 0, ancho, alto);

    view->setBackgroundBrush(QBrush(QColor(50, 50, 60)));

    jugador = new PersonajeNivel3();
    jugador->setPos(ancho/2 - 20, alto/2 - 20);
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(jugador);
    jugador->setFocus();


    QBrush colorMuro(QColor(100, 100, 100));
    QPen bordeMuro(Qt::black, 2);

    int grosor = 40;
    int tamHueco = 150;

    scene->addRect(0, 0, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);
    scene->addRect((ancho/2 + tamHueco/2), 0, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);

    scene->addRect(0, alto - grosor, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);
    scene->addRect((ancho/2 + tamHueco/2), alto - grosor, (ancho/2 - tamHueco/2), grosor, bordeMuro, colorMuro);

    scene->addRect(0, 0, grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);
    scene->addRect(0, (alto/2 + tamHueco/2), grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);

    scene->addRect(ancho - grosor, 0, grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);
    scene->addRect(ancho - grosor, (alto/2 + tamHueco/2), grosor, (alto/2 - tamHueco/2), bordeMuro, colorMuro);


    int largoL = 150;
    int grosorL = 40;

    int centroX = ancho / 2;
    int centroY = alto / 2;
    int separacion = 100; // Distancia del centro a la esquina interna de la L

    scene->addRect(centroX - separacion - grosorL, centroY - separacion - largoL, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX - separacion - largoL, centroY - separacion - grosorL, largoL, grosorL, bordeMuro, colorMuro);

    scene->addRect(centroX + separacion, centroY - separacion - largoL, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX + separacion, centroY - separacion - grosorL, largoL, grosorL, bordeMuro, colorMuro);

    scene->addRect(centroX - separacion - grosorL, centroY + separacion, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX - separacion - largoL, centroY + separacion, largoL, grosorL, bordeMuro, colorMuro);


    scene->addRect(centroX + separacion, centroY + separacion, grosorL, largoL, bordeMuro, colorMuro);
    scene->addRect(centroX + separacion, centroY + separacion, largoL, grosorL, bordeMuro, colorMuro);
}
