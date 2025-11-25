#ifndef PANTALLANIVEL3_H
#define PANTALLANIVEL3_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "personajenivel3.h"

class PantallaNivel3 : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaNivel3(QWidget *parent = nullptr);

private:
    void crearEscenario();

    QGraphicsScene *scene;
    QGraphicsView *view;
    PersonajeNivel3 *jugador;
    QTimer *gameTimer;
};

#endif
