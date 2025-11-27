#include "personaje.h"
#include "isla.h"
#include "cajaArma.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QPainter>

Personaje::Personaje(QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPixmapItem(parent),
    velocidadMax(5.0),
    ancho(50),
    alto(50),
    vida(VIDA_INICIAL),
    vidasRestantes(VIDAS_INICIALES)
{
    QPixmap pixmapEsfera(ancho, alto);
    pixmapEsfera.fill(Qt::transparent);
    QPainter painter(&pixmapEsfera);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(1, 1, ancho-2, alto-2);
    painter.end();
    setPixmap(pixmapEsfera);
}

void Personaje::setVelocidadMax(qreal nuevaVelocidad)
{
    velocidadMax = nuevaVelocidad;
}

void Personaje::setImagen(QString rutaImagen)
{
    QPixmap sprite(rutaImagen);
    if (!sprite.isNull()) {
        setPixmap(sprite.scaled(QSize(ancho, alto), Qt::KeepAspectRatio));
    }
}

void Personaje::setTamano(qreal w, qreal h)
{
    ancho = w;
    alto = h;
    if (!pixmap().isNull()) {
        setPixmap(pixmap().scaled(QSize(ancho, alto), Qt::IgnoreAspectRatio));
    }
}

int Personaje::getVida() const
{
    return vida;
}

int Personaje::getVidasRestantes() const
{
    return vidasRestantes;
}

void Personaje::setVida(int nuevaVida)
{
    vida = nuevaVida;
    if (vida > VIDA_INICIAL) vida = VIDA_INICIAL;

    if (vida <= 0) {
        vida = 0;
        emit personajeMuerto();
    }
    emit vidaCambiada(vida);
}

void Personaje::setVidasRestantes(int nuevasVidas)
{
    vidasRestantes = nuevasVidas;
    if (vidasRestantes < 0) vidasRestantes = 0;
    emit vidasCambiadas(vidasRestantes);
}

void Personaje::recibirDano(int cantidad)
{
    setVida(vida - cantidad);
}

void Personaje::reiniciarPersonaje()
{
    setVidasRestantes(vidasRestantes - 1);
    if (vidasRestantes > 0) {
        setVida(VIDA_INICIAL);
        setPos(0, 0);
    }
}

bool Personaje::canMoveTo(qreal newX, qreal newY)
{
    if (!scene()) return false;
    QRectF sceneRect = scene()->sceneRect();
    QRectF newPlayerRect(newX, newY, ancho, alto);
    if (!sceneRect.contains(newPlayerRect)) {
        return false;
    }

    QPointF oldPos = pos();
    setPos(newX, newY);
    QList<QGraphicsItem*> colliding_items = collidingItems();
    setPos(oldPos);

    for (QGraphicsItem *item : colliding_items) {
        if (dynamic_cast<CajaArma*>(item)) {
            continue;
        }

        if (dynamic_cast<Isla*>(item)) {
            return false;
        }

        if (dynamic_cast<QGraphicsRectItem*>(item)) {
            return false;
        }
    }
    return true;
}
