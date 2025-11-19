#ifndef PANTALLANIVEL2_H
#define PANTALLANIVEL2_H

#include <QDialog>
#include <QGraphicsScene>
#include "cannonball.h"

namespace Ui {
class pantallaNivel2;
}

class pantallaNivel2 : public QDialog
{
    Q_OBJECT

public:
    explicit pantallaNivel2(QWidget *parent = nullptr);
    ~pantallaNivel2();

private slots:
    void on_pushButton_clicked();


    void on_btnDisparar_clicked();

private:
    Ui::pantallaNivel2 *ui;
    QGraphicsScene *m_scene;
    CannonBall *m_bola;
};

#endif // PANTALLANIVEL2_H
