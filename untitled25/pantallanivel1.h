#ifndef PANTALLANIVEL1_H
#define PANTALLANIVEL1_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include "balacanon.h"
#include "PersonajeNivel1.h"
#include "isla.h"

class PantallaNivel1 : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaNivel1(QWidget *parent = nullptr);

public slots:
    void actualizarVida(int vida);
    void actualizarVidas(int vidas);
    void generarBala();
    void generarIsla();
    void manejarMuerte();
    void reanudarSpawns();
    void actualizarCronometro();

private:
    void crearEscenario();
    void crearHUD();
    void mostrarGameOver();
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
};

#endif
