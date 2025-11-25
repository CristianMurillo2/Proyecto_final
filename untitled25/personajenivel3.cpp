#include "personajenivel3.h"
#include "arma.h"
#include <QGraphicsScene>
#include <QPainter>

PersonajeNivel3::PersonajeNivel3(QGraphicsItem *parent)
    : Personaje(parent),
    w(false), a(false), s(false), d(false),
    puedeDisparar(true),
    ultimaDirX(0), ultimaDirY(1)
{
    QPixmap skin(40, 40);
    skin.fill(Qt::transparent);
    QPainter p(&skin);
    p.setBrush(Qt::cyan);
    p.setPen(QPen(Qt::black, 2));
    p.drawRect(2, 2, 36, 36);
    p.setBrush(Qt::black);
    p.drawEllipse(18, 18, 4, 4);
    p.end();
    setPixmap(skin);

    setVelocidadMax(5.0);
}

void PersonajeNivel3::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W: w = true; break;
    case Qt::Key_S: s = true; break;
    case Qt::Key_A: a = true; break;
    case Qt::Key_D: d = true; break;

    case Qt::Key_C:
        if (puedeDisparar) {
            disparar();
        }
        break;
    }
}

void PersonajeNivel3::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W: w = false; break;
    case Qt::Key_S: s = false; break;
    case Qt::Key_A: a = false; break;
    case Qt::Key_D: d = false; break;
    }
}

void PersonajeNivel3::actualizarMovimiento()
{
    qreal dx = 0;
    qreal dy = 0;

    if (w) dy -= 1;
    if (s) dy += 1;
    if (a) dx -= 1;
    if (d) dx += 1;
        if (dx != 0 || dy != 0) {
        ultimaDirX = dx;
        ultimaDirY = dy;
    }

    qreal moveX = dx * velocidadMax;
    qreal moveY = dy * velocidadMax;

    if (moveX != 0 && canMoveTo(x() + moveX, y())) {
        setPos(x() + moveX, y());
    }
    if (moveY != 0 && canMoveTo(x(), y() + moveY)) {
        setPos(x(), y() + moveY);
    }
}

void PersonajeNivel3::disparar()
{
    if (!scene()) return;

    qreal centroX = x() + boundingRect().width() / 2 - 5;
    qreal centroY = y() + boundingRect().height() / 2 - 5;

    Arma *disparo = new Arma(centroX, centroY, ultimaDirX, ultimaDirY);
    scene()->addItem(disparo);

    puedeDisparar = false;
    QTimer::singleShot(500, [this](){
        puedeDisparar = true;
    });
}

