#ifndef REGLAS_JUEGO_H
#define REGLAS_JUEGO_H

#include <QObject>
#include <QKeyEvent>
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>


class reglas_juego
{
public:
    reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels);
    ~reglas_juego();
    void key_event(QKeyEvent *event);
    void Set_game_keys();

private:
    unsigned int game_keys[4];
    void set_game_keys;
};

#endif // REGLAS_JUEGO_H
