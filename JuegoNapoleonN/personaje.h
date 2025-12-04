#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Personaje(QGraphicsItem *parent = nullptr);

    void setVelocidadMax(qreal nuevaVelocidad);
    void setImagen(QString rutaImagen);
    void setTamano(qreal w, qreal h);

    int getVida() const;
    int getVidasRestantes() const;
    void setVida(int nuevaVida);
    void setVidasRestantes(int nuevasVidas);
    void recibirDano(int cantidad);
    void reiniciarPersonaje();

signals:
    void vidaCambiada(int vidaActual);
    void vidasCambiadas(int vidasActuales);
    void personajeMuerto();
    void gameOver();

protected:
    bool canMoveTo(qreal newX, qreal newY);

    qreal velocidadMax;
    qreal ancho;
    qreal alto;
    int vida;
    int vidasRestantes;

    static const int VIDA_INICIAL = 100;
    static const int VIDAS_INICIALES = 1;
};

#endif
