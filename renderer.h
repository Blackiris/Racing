#ifndef RENDERER_H
#define RENDERER_H

#include "Backend/IBackend.h"
#include "level.h"

class Renderer
{
public:
    Renderer(IBackend &backend);
    void draw_ground(const Level& level, const unsigned int &z_advance);
    void draw_cars(std::list<Car> cars, const unsigned int &z_advance);

private:
    IBackend &m_backend;
    float draw_ground_line(const Level& level, const RoadSection &section, const unsigned int &z_advance, const int &z_ground, const unsigned int &screen_y,
                           const float &previous_section_delta, const float& previous_section_delta_diff, const unsigned int &previous_section_screen_y);
    int get_screeny_from_zground(const unsigned int &z_ground);
    void draw_car(Car car, const unsigned int &z_advance);
};

#endif // RENDERER_H
