#include "movimientoparticula.h"

double movimientoParticula::getPosx() const
{
    return posx;
}

double movimientoParticula::getPosy() const
{
    return posy;
}

movimientoParticula::movimientoParticula()
{

}

movimientoParticula::movimientoParticula(double x, double y, double v, double a)
{
    tiempo = 0.01;
    g = -9.8;
    posx = x;
    posy = y;
    vel = v;
    ang = a;
}

void movimientoParticula::calcularVelocidad()
{
    velx = vel*cos(ang);
    vely = vel*sin(ang)+g*tiempo;

}

void movimientoParticula::calcularPosicion()
{
    posx += velx*tiempo;
    posy += vely*tiempo+(0.5*g*tiempo*tiempo);
}

void movimientoParticula::actualizarVelocidad()
{
    vel = sqrt(pow(velx,2)+pow(vely,2));
    ang = atan2(vely, velx);
}
