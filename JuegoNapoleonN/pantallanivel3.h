#ifndef PANTALLANIVEL3_H
#define PANTALLANIVEL3_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QList>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QSoundEffect>
#include "personajenivel3.h"
#include "cajaArma.h"
#include "enemigo.h"

class PantallaNivel3 : public QDialog
{
    Q_OBJECT

public:
    explicit PantallaNivel3(QWidget *parent = nullptr);
    ~PantallaNivel3();

public slots:
    void generarCajaArma();
    void generarEnemigo();
    void enemigoEliminado();
    void detenerJuego();
    void actualizarContadorVida(int vida);

private:
    void crearEscenario();
    void rellenarBolsa();
    void iniciarNuevaOleada();
    void mostrarVictoria();
    QGraphicsScene *scene;
    QGraphicsView *view;
    PersonajeNivel3 *jugador;
    QTimer *gameTimer;
    QTimer *timerItems;
    QTimer *timerSpawns;
    int oleadaActual;
    int enemigosPorGenerar;
    int enemigosVivos;
    QList<TipoArma> bolsaArmas;
    TipoArma ultimaArmaGenerada;
    QSoundEffect *musicaFondo;
    QGraphicsTextItem *textoOleada;
    QGraphicsTextItem *textoVida;
};

#endif
