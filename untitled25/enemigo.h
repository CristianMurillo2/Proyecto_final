#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "personajenivel3.h"

class Enemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemigo(PersonajeNivel3* objetivo, QGraphicsItem *parent = nullptr);
    void recibirDano(int cantidad);

public slots:
    void mover();
    void disparar();

signals:
    void enemigoMuerto();

private:
    PersonajeNivel3* target;
    int vida;
    qreal velocidad;
    int tiempoVivo;

    QTimer *timerIA;
    QTimer *timerDisparo;
};

#endif
