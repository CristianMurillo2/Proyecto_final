#ifndef CAJA_ARMA_H
#define CAJA_ARMA_H

#include <QGraphicsPixmapItem>
#include <QObject>

enum TipoArma {
    NORMAL,
    ESCOPETA,
    SNIPER,
    METRALLETA
};

class CajaArma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CajaArma(qreal x, qreal y, TipoArma tipo);

public slots:
    void verificarColision();

private:
    TipoArma tipoCaja;
};

#endif
