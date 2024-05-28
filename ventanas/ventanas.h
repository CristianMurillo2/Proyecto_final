#ifndef VENTANAS_H
#define VENTANAS_H

#include <QMainWindow>
#include "reglas_juego.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class ventanas; }
QT_END_NAMESPACE

class ventanas : public QMainWindow
{
    Q_OBJECT

public:
    ventanas(QWidget *parent = nullptr);
    ~ventanas();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::ventanas *ui;
    reglas_juego *game;

    void setup_game_rules();
};
#endif // VENTANAS_H
