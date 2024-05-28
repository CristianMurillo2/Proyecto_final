#include "personaje.h"

personaje::personaje(unsigned int scale){
    pixmap_management = new sprites(":/sprites.png",scale);
    pixmap_management->cut_character_pixmap(set_complete_sprites());
    pixmap_management->set_design_size(character_pixel_x_size,
                                       character_pixel_y_size);
    //setPixmap();
    set_animations();
    setX(32);
    setY(32);
    setPixmap(pixmap_management->get_current_pixmap(3));
}
void personaje::set_keys(unsigned int *keys)
{
    for(unsigned int i=0;i<4;i++) this->keys[i] = keys[i];
}
