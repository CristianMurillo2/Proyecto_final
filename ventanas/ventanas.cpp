#include "ventanas.h"
#include "ui_ventanas.h"

ventanas::ventanas(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ventanas)
{
    ui->setupUi(this);
    setup_game_rules();
}

ventanas::~ventanas()
{
    delete ui;
    delete game;
}

void ventanas::keyPressEvent(QKeyEvent *event)
{
    game->key_event(event);
}

void ventanas::setup_game_rules()
{
    QVector<QLabel *> labels;

    labels.push_back(ui->L_Points);
    labels.push_back(ui->L_life);
    labels.push_back(ui->L_life_counter);
    labels.push_back(ui->L_time);
    labels.push_back(ui->L_time_counter);

    game = new reglas_juego(ui->graphicsView,labels);
}
