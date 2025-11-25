#include "arma.h"
#include "enemigo.h"
#include "personajenivel3.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QtMath>
#include <QGraphicsRectItem>

Arma::Arma(qreal x, qreal y, qreal dirX, qreal dirY, int rango, bool perforante, bool esDelEnemigo, QGraphicsItem *parent)
    : QObject(nullptr), QGraphicsPixmapItem(parent), esPerforante(perforante), esEnemigo(esDelEnemigo)
{
    QPixmap pixmap(10, 10);
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);

    if (esEnemigo) p.setBrush(Qt::darkMagenta);
    else p.setBrush(esPerforante ? Qt::red : Qt::yellow);

    p.setPen(Qt::NoPen);
    p.drawEllipse(0, 0, 10, 10);
    p.end();
    setPixmap(pixmap);
    setPos(x, y);

    qreal velocidad = esEnemigo ? 6.0 : (esPerforante ? 20.0 : 10.0);
    qreal longitud = qSqrt(dirX*dirX + dirY*dirY);

    if (longitud != 0) {
        velX = (dirX / longitud) * velocidad;
        velY = (dirY / longitud) * velocidad;
    } else {
        velX = velocidad; velY = 0;
    }

    pasosRestantes = rango;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Arma::mover);
    timer->start(20);
}

int Arma::getDano() const {
    if (esPerforante) return 3;
    return 1;
}

void Arma::mover()
{
    setPos(x() + velX, y() + velY);

    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {

        if (dynamic_cast<QGraphicsRectItem*>(item) && !dynamic_cast<Arma*>(item)) {
            if (scene()) scene()->removeItem(this);
            delete this;
            return;
        }

        if (esEnemigo) {
            PersonajeNivel3 *jugador = dynamic_cast<PersonajeNivel3*>(item);
            if (jugador) {
                jugador->recibirDano();
                if (scene()) scene()->removeItem(this);
                delete this;
                return;
            }
        }

        else {
            Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
            if (enemigo) {
                enemigo->recibirDano(getDano());
                if (!esPerforante) {
                    if (scene()) scene()->removeItem(this);
                    delete this;
                    return;
                }
            }
        }
    }

    pasosRestantes--;
    if (pasosRestantes <= 0 || x() < -50 || x() > 1300 || y() < -50 || y() > 800) {
        if (scene()) scene()->removeItem(this);
        delete this;
    }
}
