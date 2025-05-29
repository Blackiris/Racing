#ifndef IBACKEND_H
#define IBACKEND_H

#include <list>
#include <string>


#include "../car.h"
#include "../level.h"

enum KeyName {
    UP, DOWN, LEFT, RIGHT
};

struct Sprite {
    unsigned int x;
    unsigned int y;
    std::string image;
};

class IBackend {
public:
    virtual void init_window(const int &screenWidth, const int &screenHeight) = 0;
    virtual bool should_close() = 0;
    virtual void begin_draw() = 0;
    virtual void end_draw() = 0;
    virtual void draw_back_sprites(const unsigned int &z_advance, const Level& level, std::list<Sprite*> sprites) = 0;
    virtual void draw_car_info(const Car& car) = 0;
    virtual void close() = 0;

    virtual bool isKeyDown(const KeyName &keyname) = 0;
};

#endif // IBACKEND_H
