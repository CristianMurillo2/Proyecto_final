#ifndef PANTALLANIVEL1_H
#define PANTALLANIVEL1_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "PersonajeNivel1.h"

class PantallaNivel1 : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaNivel1(QWidget *parent = nullptr);

private:
    void crearEscenario();

    QGraphicsScene *scene;
    QGraphicsView *view;
    PersonajeNivel1 *jugador;
    QTimer *gameTimer;
};

#endif
