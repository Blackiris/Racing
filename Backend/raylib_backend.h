#ifndef RAYLIB_BACKEND_H
#define RAYLIB_BACKEND_H

#include "IBackend.h"
#include "raylib.h"

#include <map>

class RayLibBackend : public IBackend
{
private:

    std::map<std::string, Texture2D> pathToTexture;
    Texture2D getTexture(const std::string &path);

public:
    RayLibBackend();
    void init_window(const int &screenWidth, const int &screenHeight) override;
    bool should_close() override;
    void begin_draw() override;
    void end_draw() override;
    void clear_background() override;
    void draw_sprites(std::list<Sprite*> sprites) override;
    void draw_sprite(const Sprite* sprite) override;
    void draw_rectangle(int posX, int posY, int width, int height, BackColor color) override;
    void draw_car_info(const Car& car) override;
    void close() override;

    bool isKeyDown(const KeyName &keyname) override;
};

#endif // RAYLIB_BACKEND_H
