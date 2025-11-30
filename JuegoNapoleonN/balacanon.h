#ifndef BALACANON_H
#define BALACANON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsRectItem>

enum TipoDisparo {
    LINEAL,
    PARABOLICO,
    OSCILANTE,
    ESPIRAL,
    ZIGZAG
};

class BalaCanon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    BalaCanon(qreal startX, qreal startY, qreal vX, qreal vY, TipoDisparo tipo, QGraphicsItem *parent = nullptr);
    void setImagen(QString rutaImagen);


public slots:
    void mover();

private:
    qreal velocidadX;
    qreal velocidadY;
    qreal ancho;
    qreal alto;
    QTimer *timerMovimiento;
    int dano;
    TipoDisparo tipoMovimiento;
    double tiempoVida;
    qreal baseVX, baseVY;
    qreal inicioX;
    qreal inicioY;
};

#endif // BALACANON_H
