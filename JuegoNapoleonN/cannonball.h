#ifndef CANNONBALL_H
#define CANNONBALL_H

#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QGraphicsScene>
#include "movimientoparticula.h"

class CannonBall : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    CannonBall(double x, double y, double v, double a, QGraphicsScene *scene, QObject *parent = nullptr);
    ~CannonBall();

public slots:
    void actualizarPosicion();

private:
    movimientoParticula *m_fisica;
    QTimer *m_timer;
    QGraphicsScene *m_scene;
    const double escala = 20.0;
    const int diametro = 10;
};

#endif // CANNONBALL_H
