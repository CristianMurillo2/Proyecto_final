#ifndef FONDO_ANIMADO_H
#define FONDO_ANIMADO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMovie>

class FondoAnimado : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    FondoAnimado(QString rutaGif, QSize tamano, QGraphicsItem *parent = nullptr);
    ~FondoAnimado();

private slots:
    void actualizarFrame();

private:
    QMovie *movie;
    QSize dimensiones;
};

#endif
