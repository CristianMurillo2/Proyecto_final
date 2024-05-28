#include "reglas_juego.h"

reglas_juego(QGraphicsView *graph, QVector<QLabel *> game_labels){
    srand(time(NULL));

    this->graph = graph;
    labels = game_labels;
    setup_scene();
}
void reglas_juego::key_event(QKeyEvent *event){

}

void reglas_juego::Set_game_keys()
{
    game_keys[0] = Qt::Key_A;
    game_keys[1] = Qt::Key_D;
    game_keys[2] = Qt::Key_W;
    game_keys[3] = Qt::Key_S;
}
