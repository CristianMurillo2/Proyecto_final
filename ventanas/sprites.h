#ifndef SPRITES_H
#define SPRITES_H
#include <QRect>
#include <QPixmap>
#include <QVector>
class sprites
{
public:
    sprites(QString main_pixmap, unsigned int scale);
    void set_design_size(unsigned int x, unsigned int y);
    void cut_character_pixmap(QRect size);
    void add_new_animation(QRect size, unsigned int number);
    QPixmap get_current_pixmap(unsigned int animation);
    QPixmap get_fixed_image(QRect size);
private:
    QPixmap *main_pixmap, *character_pixmap;
    QVector<QRect> animations;
    QVector<unsigned int> animations_size;
    unsigned int width, height, animation_counter, scale;
};

#endif // SPRITES_H
