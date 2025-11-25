#ifndef PERSONAJENIVEL3_H
#define PERSONAJENIVEL3_H

#include "personaje.h"
#include <QTimer>

class PersonajeNivel3 : public Personaje
{
    Q_OBJECT

public:
    explicit PersonajeNivel3(QGraphicsItem *parent = nullptr);

public slots:
    void actualizarMovimiento();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void disparar();
    bool w, a, s, d;
    qreal ultimaDirX;
    qreal ultimaDirY;
    bool puedeDisparar;
};

#endif
