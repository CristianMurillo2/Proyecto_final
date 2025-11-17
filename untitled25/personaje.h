#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    personaje(QGraphicsItem *parent = nullptr);
    int getVida() const;
    int getVidasRestantes() const;

signals:
    void vidaCambiada(int vidaActual);
    void vidasCambiadas(int vidasActuales);
    void personajeMuerto();
    void gameOver();

public slots:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void setVida(int nuevaVida);
    void setVidasRestantes(int nuevasVidas);
        void recibirDano(int cantidad);
    void reiniciarPersonaje();
private:
    bool canMoveTo(qreal newX, qreal newY);
    qreal velocidad;
    int vida;
    int vidasRestantes;
    static const int VIDA_INICIAL = 100;
    static const int VIDAS_INICIALES = 3;

};

#endif // PERSONAJE_H
