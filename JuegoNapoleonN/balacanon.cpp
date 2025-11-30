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
    inicioX(startX),
    inicioY(startY),
    dano(25),
    tipoMovimiento(tipo),
    tiempoVida(0)
{
    baseVX = vX;
    baseVY = vY;
    QPixmap sprite(":/recursos/cannonBall.png");
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
    qreal vx_actual = baseVX;
    qreal vy_actual = baseVY;

    switch (tipoMovimiento) {
    case LINEAL:
        break;

    case PARABOLICO:
    {
        qreal gravedad = 0.15;
        velocidadY += gravedad;
        vx_actual = velocidadX;
        vy_actual = velocidadY;
    }
    break;

    case OSCILANTE:
    {
        qreal amplitud = 20.0;
        qreal frecuencia = 2.0;
        qreal perpX = -baseVY;
        qreal perpY = baseVX;
        qreal len = qSqrt(perpX*perpX + perpY*perpY);
        if (len != 0) { perpX /= len; perpY /= len; }
        qreal factorVelocidad = amplitud * frecuencia * qCos(tiempoVida * frecuencia);
        vx_actual = baseVX + (perpX * factorVelocidad * 0.1);
        vy_actual = baseVY + (perpY * factorVelocidad * 0.1);
    }
    break;

    case ESPIRAL:
    {
        qreal radio = 16.0;
        qreal frecuencia = 3.0;
        qreal v_circulo_X = radio * frecuencia * qCos(tiempoVida * frecuencia);
        qreal v_circulo_Y = radio * frecuencia * qSin(tiempoVida * frecuencia);

        vx_actual = baseVX + (v_circulo_X * 0.1);
        vy_actual = baseVY + (v_circulo_Y * 0.1);
    }
    break;

    case ZIGZAG:
    {
        qreal periodo = 2.0;
        qreal amplitudZigZag = 5.0;
        qreal pX = -baseVY;
        qreal pY = baseVX;
        qreal len = qSqrt(pX*pX + pY*pY);
        if (len != 0) { pX /= len; pY /= len; }
        qreal direccion = qSin(2 * M_PI * tiempoVida / periodo);
        qreal signo = (direccion >= 0) ? 1.0 : -1.0;

        vx_actual = (baseVX * 0.7) + (pX * signo * amplitudZigZag);
        vy_actual = (baseVY * 0.7) + (pY * signo * amplitudZigZag);
    }
    break;
    }
    setPos(x() + vx_actual, y() + vy_actual);
    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        Personaje *jugador = dynamic_cast<Personaje*>(item);
        if (jugador) {
            jugador->recibirDano(dano);
            if (scene()) scene()->removeItem(this);
            deleteLater();
            return;
        }
        QGraphicsRectItem *muro = dynamic_cast<QGraphicsRectItem*>(item);
        if (muro) {
            if (scene()) scene()->removeItem(this);
            deleteLater();
            return;
        }
    }
    if (x() < -100 || x() > 1400 || y() < -100 || y() > 900) {
        if (scene()) scene()->removeItem(this);
        deleteLater();
        return;
    }
    if (tiempoVida > 100.0) {
        if (scene()) scene()->removeItem(this);
        deleteLater();
        return;
    }
}
