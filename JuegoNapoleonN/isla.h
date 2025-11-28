#ifndef ISLA_H
#define ISLA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Isla : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Isla(qreal x, qreal tamano, qreal velocidadBajada, QGraphicsItem *parent = nullptr);

public slots:
    void mover();

private:
    QTimer *timerMovimiento;
    qreal velocidad;
};

#endif
