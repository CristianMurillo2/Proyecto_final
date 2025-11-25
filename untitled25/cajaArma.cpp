#include "cajaArma.h"
#include "personajenivel3.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

CajaArma::CajaArma(qreal x, qreal y, TipoArma tipo)
    : tipoCaja(tipo)
{
    QString rutaHoja = "C:\\Users\\crist\\OneDrive\\Escritorio\\proyecto final\\build-untitled25-Desktop_Qt_6_5_3_MinGW_64_bit-Debug\\armas.png";
    QPixmap hojaCompleta(rutaHoja);

    QPixmap spriteFinal;
    QColor colorRespaldo;

    if (hojaCompleta.isNull()) {
        qDebug() << "ERROR: No se pudo cargar la hoja de items en" << rutaHoja;
        switch (tipo) {
        case ESCOPETA:  colorRespaldo = Qt::darkGreen; break;
        case SNIPER:    colorRespaldo = Qt::darkRed;   break;
        case METRALLETA:colorRespaldo = Qt::darkBlue;  break;
        default:        colorRespaldo = Qt::gray;      break;
        }

        spriteFinal = QPixmap(40, 40);
        spriteFinal.fill(colorRespaldo);
        QPainter p(&spriteFinal);
        p.setPen(Qt::white);
        p.drawRect(0,0,39,39);
        p.drawText(QRect(0,0,40,40), Qt::AlignCenter, "?");
        p.end();

    } else {

        int recorteX = 0;
        int recorteY = 0;
        int anchoSprite = 150;
        int altoSprite = 140;

        switch (tipo) {
        case ESCOPETA:
            recorteX = 735;
            recorteY = 75;
            break;

        case SNIPER:
            recorteX = 735;
            recorteY = 390;
            break;

        case METRALLETA:
            recorteX = 070;
            recorteY = 230;
            break;

        default:
            recorteX = 0; recorteY = 0;
            break;
        }

        QPixmap recorte = hojaCompleta.copy(recorteX, recorteY, anchoSprite, altoSprite);

        spriteFinal = recorte.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    setPixmap(spriteFinal);
    setPos(x, y);
    setZValue(1);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CajaArma::verificarColision);
    timer->start(50);
}

void CajaArma::verificarColision()
{
    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem *item : colisiones) {
        PersonajeNivel3 *jugador = dynamic_cast<PersonajeNivel3*>(item);
        if (jugador) {
            jugador->cambiarArma(tipoCaja, 10000);
            if (scene()) scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
