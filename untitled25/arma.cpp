#include "arma.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QtMath>
#include <QGraphicsRectItem>

Arma::Arma(qreal x, qreal y, qreal dirX, qreal dirY, QGraphicsItem *parent)
    : QObject(nullptr), QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(10, 10);
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);
    p.setBrush(Qt::yellow);
    p.setPen(Qt::NoPen);
    p.drawEllipse(0, 0, 10, 10);
    p.end();
    setPixmap(pixmap);

    setPos(x, y);

    qreal velocidadBala = 10.0;

    qreal longitud = qSqrt(dirX*dirX + dirY*dirY);
    if (longitud != 0) {
        velX = (dirX / longitud) * velocidadBala;
        velY = (dirY / longitud) * velocidadBala;
    } else {
        velX = velocidadBala;
        velY = 0;
    }

    pasosRestantes = 25;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Arma::mover);
    timer->start(20);
}

void Arma::mover()
{
    setPos(x() + velX, y() + velY);

    QList<QGraphicsItem*> colisiones = collidingItems();

    for (QGraphicsItem *item : colisiones) {

        QGraphicsRectItem *muro = dynamic_cast<QGraphicsRectItem*>(item);

        if (muro) {
            if (scene()) {
                scene()->removeItem(this);
            }
            delete this;
            return;
        }
    }

    pasosRestantes--;
    if (pasosRestantes <= 0 || x() < -50 || x() > 1300 || y() < -50 || y() > 800) {
        if (scene()) scene()->removeItem(this);
        delete this;
    }
}
