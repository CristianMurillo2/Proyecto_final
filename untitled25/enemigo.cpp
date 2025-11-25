#include "enemigo.h"
#include "arma.h"
#include <QtMath>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>

Enemigo::Enemigo(PersonajeNivel3* objetivo, QGraphicsItem *parent)
    : QObject(nullptr), QGraphicsPixmapItem(parent), target(objetivo)
{
    QPixmap skin(40, 40); skin.fill(Qt::transparent); QPainter p(&skin);
    p.setBrush(Qt::red); p.setPen(QPen(Qt::black, 2)); p.drawEllipse(2, 2, 36, 36);
    p.setBrush(Qt::yellow); p.drawEllipse(10, 10, 8, 8); p.drawEllipse(22, 10, 8, 8);
    p.end();
    setPixmap(skin);

    vida = 3;
    velocidad = 2.0;
    tiempoVivo = 0;

    timerIA = new QTimer(this);
    connect(timerIA, &QTimer::timeout, this, &Enemigo::mover);
    timerIA->start(30);

    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &Enemigo::disparar);
    timerDisparo->start(QRandomGenerator::global()->bounded(2000, 4000));
}

void Enemigo::recibirDano(int cantidad)
{
    vida -= cantidad;
    if (vida <= 0) {
        emit enemigoMuerto();
        if (scene()) scene()->removeItem(this);
        delete this;
    }
}

void Enemigo::disparar()
{
    if (!target || !scene()) return;

    qreal dx = target->x() - x();
    qreal dy = target->y() - y();

    Arma *bala = new Arma(x() + 20, y() + 20, dx, dy, 15, false, true);
    scene()->addItem(bala);
}

void Enemigo::mover()
{
    if (!target || !scene()) return;

    tiempoVivo++;
    if (tiempoVivo == 200) {
        velocidad += 1.5;
        setOpacity(0.7);
    }

    qreal dx = target->x() - x();
    qreal dy = target->y() - y();
    qreal angulo = qAtan2(dy, dx);

    qreal vx = qCos(angulo) * velocidad;
    qreal vy = qSin(angulo) * velocidad;

    setPos(x() + vx, y() + vy);
}
