#ifndef PANTALLANIVEL2_H
#define PANTALLANIVEL2_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "cannonball.h"
#include <QPainter>
#include <Qimage.h>
#include <QPixmap.h>
#include <QTimer>
#define _USE_MATH_DEFINES
#include <cmath>
#include <QList>
#include <QSoundEffect>

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
    void on_verticalSlider_valueChanged(int value);
    void verificarColisiones();
    void actualizarCronometro();
    void reiniciarJuego();

private:
    void iniciarNivel();
    Ui::pantallaNivel2 *ui;
    QGraphicsScene *m_scene;
    CannonBall *m_bola;
    QGraphicsPixmapItem *cannon;
    QGraphicsPixmapItem *base;
    QGraphicsPixmapItem *banderaF;
    QGraphicsPixmapItem *banderaB;
    QList <QGraphicsPixmapItem*> obst;
    double m_anguloGrados;
    QTimer *timerColisiones;
    QPixmap imagenTiendaNormal;
    QPixmap imagenTiendaRota;
    void finalizarJuego(bool ganado);
    QTimer *timerJuego;
    int tiempoRestante;
    QSoundEffect *sonidoDisparo;
};

#endif // PANTALLANIVEL2_H
