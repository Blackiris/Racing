#ifndef IBACKEND_H
#define IBACKEND_H

#include <cstdint>
#include <list>
#include <string>


#include "../car.h"

enum KeyName {
    UP, DOWN, LEFT, RIGHT
};

struct Sprite {
    unsigned int x;
    unsigned int y;
    std::string image;
};

#define GRAY       BackColor{ 130, 130, 130, 255 }   // Gray
#define LIGHTGREEN BackColor{ 9, 168, 42, 255 }
#define GREEN      BackColor{ 0, 228, 48, 255 }
#define WHITE      BackColor{ 255, 255, 255, 255 }   // White

typedef struct BackColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} BackColor;

class IBackend {
public:
    virtual void init_window(const int &screenWidth, const int &screenHeight) = 0;
    virtual bool should_close() = 0;
    virtual void begin_draw() = 0;
    virtual void end_draw() = 0;
    virtual void clear_background() = 0;
    virtual void draw_sprites(std::list<Sprite*> sprites) = 0;
    virtual void draw_sprite(const Sprite* sprite) = 0;
    virtual void draw_rectangle(int posX, int posY, int width, int height, BackColor color) = 0;
    virtual void draw_car_info(const Car& car) = 0;
    virtual void close() = 0;

    virtual bool isKeyDown(const KeyName &keyname) = 0;

    unsigned int screenWidth, screenHeight;
};

#endif // IBACKEND_H
