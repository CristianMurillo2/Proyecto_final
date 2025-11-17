#include "personaje.h"
#include <QPixmap>
#include <QGraphicsScene>

personaje::personaje(QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPixmapItem(parent),
    velocidad(5.0),
    vida(VIDA_INICIAL),
    vidasRestantes(VIDAS_INICIALES)
{
    // El cuerpo del constructor
    QPixmap sprite(":/sprites/personaje.png");
    setPixmap(sprite.scaled(QSize(50, 70), Qt::KeepAspectRatio));
}

int personaje::getVida() const
{
    return vida;
}

int personaje::getVidasRestantes() const
{
    return vidasRestantes;
}

void personaje::setVida(int nuevaVida)
{
    vida = nuevaVida;
    if (vida > VIDA_INICIAL) {
        vida = VIDA_INICIAL;
    }

    if (vida <= 0) {
        vida = 0;
        emit personajeMuerto();
    }

    emit vidaCambiada(vida);
}

void personaje::setVidasRestantes(int nuevasVidas)
{
    vidasRestantes = nuevasVidas;

    if (vidasRestantes < 0) {
        vidasRestantes = 0;
        emit gameOver(); // Emite la señal de juego terminado
    }

    emit vidasCambiadas(vidasRestantes);
}

void personaje::recibirDano(int cantidad)
{
    setVida(vida - cantidad);
}

void personaje::reiniciarPersonaje()
{
    setVidasRestantes(vidasRestantes - 1);
        if (vidasRestantes > 0) {
        setVida(VIDA_INICIAL);
        setPos(0, 0);
    }
}

void personaje::moveLeft()
{
    qreal newX = x() - velocidad;
    if (canMoveTo(newX, y())) {
        setPos(newX, y());
    }
}

void personaje::moveRight()
{
    qreal newX = x() + velocidad;
    if (canMoveTo(newX, y())) {
        setPos(newX, y());
    }
}

void personaje::moveUp()
{
    qreal newY = y() - velocidad;
    if (canMoveTo(x(), newY)) {
        setPos(x(), newY);
    }
}

void personaje::moveDown()
{
    qreal newY = y() + velocidad;
    if (canMoveTo(x(), newY)) {
        setPos(x(), newY);
    }
}

bool personaje::canMoveTo(qreal newX, qreal newY)
{
    QPointF oldPos = pos();
    setPos(newX, newY);

    QList<QGraphicsItem*> colliding_items = collidingItems();

    setPos(oldPos);

    for (QGraphicsItem *item : colliding_items) {
        if (item->type() == QGraphicsRectItem::Type) {
            return false;
        }
    }

    return true;
}
