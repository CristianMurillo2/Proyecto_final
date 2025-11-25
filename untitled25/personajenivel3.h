#ifndef PERSONAJENIVEL3_H
#define PERSONAJENIVEL3_H

#include "personaje.h"
#include "cajaArma.h"
#include <QTimer>
#include <QSoundEffect>

class Arma;

class PersonajeNivel3 : public Personaje
{
    Q_OBJECT
public:
    explicit PersonajeNivel3(QGraphicsItem *parent = nullptr);
    void cambiarArma(TipoArma nuevoTipo, int duracionMs);
    void recibirDano();

signals:
    void jugadorMuerto();
    void vidaCambiada(int nuevaVida);

public slots:
    void actualizarMovimiento();
    void restaurarArma();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void disparar();

    bool w, a, s, d;
    qreal ultimaDirX, ultimaDirY;
    bool puedeDisparar;

    TipoArma armaActual;
    int tiempoCooldown;
    QTimer *timerPoder;

    QSoundEffect *sonidoDisparo;
    QSoundEffect *sonidoPowerUp;

    int vida;
};

#endif
