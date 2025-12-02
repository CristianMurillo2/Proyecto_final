#ifndef PERSONAJE_INERCIA_H
#define PERSONAJE_INERCIA_H

#include "personaje.h"
#include <QKeyEvent>

class PersonajeNivel1 : public Personaje
{
    Q_OBJECT

public:
    explicit PersonajeNivel1(QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void actualizarFisica();

private:
    qreal velX;
    qreal velY;
    qreal aceleracion;
    qreal friccion;
    bool left;
    bool right;
    bool up;
    bool down;
};

#endif
