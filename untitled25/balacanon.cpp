#include "balacanon.h"
#include "personaje.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QtMath>

BalaCanon::BalaCanon(qreal startX, qreal startY, qreal vX, qreal vY, TipoDisparo tipo, QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPixmapItem(parent),
    velocidadX(vX),
    velocidadY(vY),
    dano(25),
    tipoMovimiento(tipo),
    tiempoVida(0)
{
    baseVX = vX;
    baseVY = vY;

    QPixmap sprite("C:\\Users\\crist\\OneDrive\\Escritorio\\proyecto final\\build-untitled25-Desktop_Qt_6_5_3_MinGW_64_bit-Debug\\imagenes_barco\\PNG\\Retina\\Ship parts\\cannonBall.png");

    setPixmap(sprite.scaled(20, 20, Qt::KeepAspectRatio));

    setPos(startX, startY);
    setZValue(5);
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &BalaCanon::mover);
    timerMovimiento->start(20);
}


void BalaCanon::mover()
{
    tiempoVida += 0.1;

    qreal dx = 0;
    qreal dy = 0;

    switch (tipoMovimiento) {
    case LINEAL:
        dx = baseVX;
        dy = baseVY;
        break;

    case PARABOLICO:
        baseVY += 0.15;
        dx = baseVX;
        dy = baseVY;
        break;

    case OSCILANTE:
    {

        dx = baseVX;
        dy = baseVY;

        qreal perpX = -baseVY;
        qreal perpY = baseVX;

        qreal len = qSqrt(perpX*perpX + perpY*perpY);
        if (len != 0) { perpX /= len; perpY /= len; }

        qreal amplitud = 4.0 * qSin(tiempoVida * 2.0);
        dx += perpX * amplitud;
        dy += perpY * amplitud;
    }
    break;

    case ESPIRAL:
    {
        dx = baseVX + (5.0 * qCos(tiempoVida * 3.0));
        dy = baseVY + (5.0 * qSin(tiempoVida * 3.0));
    }
    break;

    case ZIGZAG:
    {
        if (int(tiempoVida * 10) % 20 < 10) {
            dx = baseVX + baseVY;
            dy = baseVY - baseVX;
        } else {
            dx = baseVX - baseVY;
            dy = baseVY + baseVX;
        }
        dx *= 0.7; dy *= 0.7;
    }
    break;
    }

    setPos(x() + dx, y() + dy);

        QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Personaje *jugador = dynamic_cast<Personaje*>(item);
        if (jugador) {
            jugador->recibirDano(dano);
            if (scene()) scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (x() < -200 || x() > 1000 || y() > 800 || y() < -200) {
        if (scene()) scene()->removeItem(this);
        delete this;
    }
}
