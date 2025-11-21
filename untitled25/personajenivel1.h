#ifndef PERSONAJE_INERCIA_H
#define PERSONAJE_INERCIA_H

#include "personaje.h"

class PersonajeNivel1 : public Personaje
{
    Q_OBJECT

public:
    explicit PersonajeNivel1(QGraphicsItem *parent = nullptr);

public slots:
    void actualizarFisica();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

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
