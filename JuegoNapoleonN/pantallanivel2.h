#ifndef PANTALLANIVEL2_H
#define PANTALLANIVEL2_H

#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "cannonball.h"
#include <QPainter>
#include <Qimage.h>
#include <QPixmap.h>
#include <QTimer>
#define _USE_MATH_DEFINES
#include <cmath>
#include <QList>
#include <QSoundEffect>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class pantallaNivel2;
}

class pantallaNivel2 : public QWidget
{
    Q_OBJECT

public:
    explicit pantallaNivel2(QWidget *parent = nullptr);
    ~pantallaNivel2();

signals:
    void regresarAlMenu();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnDisparar_clicked();
    void on_verticalSlider_valueChanged(int value);
    void verificarColisiones();
    void actualizarCronometro();

private:
    void iniciarNivel();
    QGraphicsTextItem *textoCronometro;
    Ui::pantallaNivel2 *ui;
    QGraphicsScene *m_scene;
    QList<CannonBall*> m_balas;
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
    QMediaPlayer *musicaFondo;
    QAudioOutput *salidaAudio;
};

#endif // PANTALLANIVEL2_H
