#ifndef RAYLIB_BACKEND_H
#define RAYLIB_BACKEND_H

#include "IBackend.h"
#include "raylib.h"

#include <map>

class RayLibBackend : public IBackend
{
private:
    unsigned int screenWidth, screenHeight;

    std::map<std::string, Texture2D> pathToTexture;
    Texture2D getTexture(const std::string &path);
    float draw_ground_line(const Level& level, const RoadSection &section, const unsigned int &z_advance, const int &z_ground, const unsigned int &screen_y,
                         const float &previous_section_delta, const float& previous_section_delta_diff, const unsigned int &previous_section_screen_y);

public:
    RayLibBackend();
    void init_window(const int &screenWidth, const int &screenHeight) override;
    bool should_close() override;
    void begin_draw() override;
    void end_draw() override;
    void draw_ground(const Level& level, const unsigned int &z_advance) override;
    void draw_sprites(std::list<Sprite*> sprites) override;
    void draw_car_info(const Car& car) override;
    void close() override;

    bool isKeyDown(const KeyName &keyname) override;
};

#endif // RAYLIB_BACKEND_H
