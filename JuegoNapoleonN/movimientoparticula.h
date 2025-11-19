#ifndef MOVIMIENTOPARTICULA_H
#define MOVIMIENTOPARTICULA_H
#include <math.h>

class movimientoParticula
{
    double posx;
    double posy;
    double vel;
    double ang;
    double velx;
    double vely;
    double tiempo;
    double g;

public:
    movimientoParticula();
    movimientoParticula(double x, double y, double v, double a);
    void calcularVelocidad();
    void calcularPosicion();
    void actualizarVelocidad();

    double getPosx() const;
    double getPosy() const;
};

#endif // MOVIMIENTOPARTICULA_H
