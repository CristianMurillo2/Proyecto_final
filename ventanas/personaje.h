#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"
#include <QGraphicsItem>
#include <QList>


#define character_pixel_x_size 16
#define character_pixel_y_size 16
#define character_speed 8
class personaje : public QObject, public QGraphicsPixmapItem
{
public:
    personaje(unsigned int scale);
    void set_keys(unsigned int *keys);
    void move(unsigned int key, bool is_valid);
    ~personaje();

};

#endif // PERSONAJE_H
