#ifndef RENDERER_H
#define RENDERER_H

#include "Backend/IBackend.h"
#include "level.h"

#include <vector>

class Renderer
{
public:
    Renderer(IBackend &backend);
    void draw(const Level& level, std::list<Car> cars, const unsigned int &z_advance);

private:
    IBackend &m_backend;
    void draw_ground_line(const Level& level, const unsigned int &z_advance, const int &z_ground, const unsigned int &screen_y,
                           const float &road_delta);
    int get_screeny_from_zground(const unsigned int &z_ground);
    float get_scale_from_zground(const unsigned int &z_ground);

    void draw_ground(const Level& level, const unsigned int &cam_z_advance, const std::vector<float> &road_deltas);
    void draw_cars(std::list<Car> cars, const unsigned int &cam_z_advance);
    void draw_car(Car car, const unsigned int &cam_z_advance);

    std::vector<float> compute_road_deltas(const Level& level, const unsigned int &cam_z_advance);
};

#endif // RENDERER_H
