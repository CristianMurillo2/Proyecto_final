#ifndef PANTALLANIVEL1_H
#define PANTALLANIVEL1_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "balacanon.h"
#include "PersonajeNivel1.h"
#include "isla.h"

class PantallaNivel1 : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaNivel1(QWidget *parent = nullptr);
    ~PantallaNivel1();

signals:
    void regresarAlMenu();

public slots:
    void actualizarVida(int vida);
    void actualizarVidas(int vidas);
    void generarBala();
    void generarIsla();
    void manejarMuerte();
    void reanudarSpawns();
    void actualizarCronometro();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void crearEscenario();
    void crearHUD();
    void mostrarGameOver(bool ganado);
    TipoDisparo obtenerSiguienteDisparo();
    QGraphicsScene *scene;
    QGraphicsView *view;
    PersonajeNivel1 *jugador;
    QTimer *gameTimer;
    QTimer *spawnTimer;
    QTimer *islaTimer;
    QTimer *timerCronometro;
    int tiempoRestante;
    QGraphicsTextItem *textoVida;
    QGraphicsTextItem *textoVidas;
    QGraphicsTextItem *textoGameOver;
    QGraphicsTextItem *textoCronometro;
    QList<TipoDisparo> bolsaDisparos;
    QMediaPlayer *musicaFondo;
    QAudioOutput *salidaAudio;
};

#endif
