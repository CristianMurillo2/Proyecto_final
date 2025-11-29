#include "isla.h"
#include "personaje.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QList>

QPixmap* Isla::texturaIsla1 = nullptr;
QPixmap* Isla::texturaIsla2 = nullptr;

Isla::Isla(qreal x, qreal tamano, qreal velocidadBajada, QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPixmapItem(parent),
    velocidad(velocidadBajada)
{
    if (texturaIsla1 == nullptr) {
        QString rutaHoja = ":/recursos/tiles_sheet.png";
        QPixmap hojaCompleta(rutaHoja);
        if (!hojaCompleta.isNull()) {
            texturaIsla1 = new QPixmap(hojaCompleta.copy(0, 0, 190, 190));
            texturaIsla2 = new QPixmap(hojaCompleta.copy(325, 0, 250, 255));
        } else {
            texturaIsla1 = new QPixmap(100, 100);
            texturaIsla1->fill(Qt::green);
            texturaIsla2 = new QPixmap(100, 100);
            texturaIsla2->fill(Qt::darkGreen);
        }
    }
    QPixmap texturaUsar;
    int tipo = QRandomGenerator::global()->bounded(0, 2);
    if (tipo == 0 && !texturaIsla1->isNull()) {
        texturaUsar = *texturaIsla1;
    } else if (!texturaIsla2->isNull()) {
        texturaUsar = *texturaIsla2;
    } else {
        texturaUsar = QPixmap(tamano, tamano);
        texturaUsar.fill(Qt::gray);
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
