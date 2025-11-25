#ifndef ARMA_H
#define ARMA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Arma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Arma(qreal x, qreal y, qreal dirX, qreal dirY, QGraphicsItem *parent = nullptr);

public slots:
    void mover();

private:
    qreal velX, velY;
    QTimer *timer;

    int pasosRestantes;
};

#endif // ARMA_H
