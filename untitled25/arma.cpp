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
    QString rutaImagen = "C:\\Users\\crist\\OneDrive\\Escritorio\\proyecto final\\build-untitled25-Desktop_Qt_6_5_3_MinGW_64_bit-Debug\\imagenes_barco\\PNG\\Retina\\Ship parts\\cannonBall.png";

    QPixmap skin(rutaImagen);

    int tamano = 15;

    if (skin.isNull()) {
        skin = QPixmap(tamano, tamano);
        skin.fill(esEnemigo ? Qt::magenta : Qt::yellow);
    }
    setPixmap(skin.scaled(tamano, tamano, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(boundingRect().center());

    setPos(x, y);
    qreal anguloRad = qAtan2(dirY, dirX);
    setRotation(qRadiansToDegrees(anguloRad));
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
