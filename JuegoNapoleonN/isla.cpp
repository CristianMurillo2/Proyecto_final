#include "isla.h"
#include "personaje.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QList>

Isla::Isla(qreal x, qreal tamano, qreal velocidadBajada, QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPixmapItem(parent),
    velocidad(velocidadBajada)
{
    static QPixmap textura1;
    static QPixmap textura2;
    static bool imagenesCargadas = false;

    if (!imagenesCargadas) {
        QString rutaHoja = ":/recursos/tiles_sheet.png";
        QPixmap hojaCompleta(rutaHoja);

        if (!hojaCompleta.isNull()) {
            textura1 = hojaCompleta.copy(0, 0, 190, 190);
            textura2 = hojaCompleta.copy(325, 0, 250, 255);
        } else {
            textura1 = QPixmap(100, 100);
            textura1.fill(Qt::green);
            textura2 = QPixmap(100, 100);
            textura2.fill(Qt::darkGreen);
        }
        imagenesCargadas = true;
    }

    QPixmap texturaUsar;
    int tipo = QRandomGenerator::global()->bounded(0, 2);

    if (tipo == 0) {
        texturaUsar = textura1;
    } else {
        texturaUsar = textura2;
    }

    setPixmap(texturaUsar.scaled(tamano, tamano, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setPos(x, -tamano);
    setZValue(1);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Isla::mover);
    timerMovimiento->start(30);
}

void Isla::mover()
{
    setPos(x(), y() + velocidad);
    if (y() > 600) {
        if (scene()) scene()->removeItem(this);
        this->deleteLater();
        return;
    }
    QList<QGraphicsItem*> colisiones = collidingItems(Qt::IntersectsItemBoundingRect);

    for (QGraphicsItem *item : colisiones) {
        Personaje *jugador = dynamic_cast<Personaje*>(item);
        if (jugador) {
            qreal limiteSuelo = 600 - 75;
            qreal nuevoY = jugador->y() + velocidad;

            if (nuevoY < limiteSuelo) {
                jugador->setPos(jugador->x(), nuevoY);
            }
            else {
                jugador->setY(limiteSuelo);
                qreal centroIsla = this->x() + (this->boundingRect().width() / 2);
                qreal centroJugador = jugador->x() + 25;
                qreal fuerzaDeslizamiento = 10.0;

                if (centroJugador < centroIsla) {
                    if (jugador->x() - fuerzaDeslizamiento > 0) {
                        jugador->setPos(jugador->x() - fuerzaDeslizamiento, jugador->y());
                    }
                }
                else {
                    if (jugador->x() + fuerzaDeslizamiento < 800 - 50) {
                        jugador->setPos(jugador->x() + fuerzaDeslizamiento, jugador->y());
                    }
                }
            }
        }
    }
}
