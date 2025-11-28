#ifndef ARMA_H
#define ARMA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Arma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Arma(qreal x, qreal y, qreal dirX, qreal dirY, int rango, bool perforante, bool esDelEnemigo, QGraphicsItem *parent = nullptr);
public slots:
    void mover();
    int getDano() const;

private:
    qreal velX, velY;
    QTimer *timer;
    int pasosRestantes;
    bool esPerforante;
    bool esEnemigo;
};

#endif // ARMA_H
