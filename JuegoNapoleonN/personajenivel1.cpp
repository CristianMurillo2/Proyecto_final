#include "PersonajeNivel1.h"
#include <cmath>

PersonajeNivel1::PersonajeNivel1(QGraphicsItem *parent)
    : Personaje(parent),
    velX(0),
    velY(0),
    aceleracion(0.5),
    friccion(0.95),
    left(false),
    right(false),
    up(false),
    down(false)
{
}

void PersonajeNivel1::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A: left = true; break;
    case Qt::Key_D: right = true; break;
    case Qt::Key_W: up = true; break;
    case Qt::Key_S: down = true; break;
    }
}

void PersonajeNivel1::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A: left = false; break;
    case Qt::Key_D: right = false; break;
    case Qt::Key_W: up = false; break;
    case Qt::Key_S: down = false; break;
    }
}

void PersonajeNivel1::actualizarFisica()
{
    if (left)  velX -= aceleracion;
    if (right) velX += aceleracion;
    if (up)    velY -= aceleracion;
    if (down)  velY += aceleracion;

    velX *= friccion;
    velY *= friccion;

    if (std::abs(velX) < 0.1) velX = 0;
    if (std::abs(velY) < 0.1) velY = 0;

    if (velX > velocidadMax) velX = velocidadMax;
    if (velX < -velocidadMax) velX = -velocidadMax;
    if (velY > velocidadMax) velY = velocidadMax;
    if (velY < -velocidadMax) velY = -velocidadMax;

    if (canMoveTo(x() + velX, y())) {
        setPos(x() + velX, y());
    } else {
        velX = 0;
    }

    if (canMoveTo(x(), y() + velY)) {
        setPos(x(), y() + velY);
    } else {
        velY = 0;
    }
}
