#include "renderer.h"
#include "levelutil.h"


int cam_dist_to_screen = 50;
int max_dist_display_road = 600;
int cam_height;
int lane_width = 150;
int road_curve_constant = 5000;



Renderer::Renderer(IBackend &backend): m_backend(backend) {
    cam_height = (cam_dist_to_screen+max_dist_display_road) * (backend.screenHeight/2)/max_dist_display_road;
}

void Renderer::draw_cars(std::list<Car> cars, const unsigned int &z_advance) {
    for (Car car : cars) {
        draw_car(car, z_advance);
    }
}

void Renderer::draw_car(Car car, const unsigned int &z_advance) {
    int screen_y = get_screeny_from_zground(car.get_zadvance_m() - z_advance);
    Sprite car_sprite = Sprite(m_backend.screenWidth/2 + car.get_xdelta() - car.get_width()/2, screen_y-car.get_height(), car.get_image());
    //std::list<Sprite*> sprites = {&car_sprite};
    m_backend.draw_sprite(&car_sprite);
}

void Renderer::draw_ground(const Level& level, const unsigned int &z_advance) {
    m_backend.clear_background();

    float previous_delta = 0, previous_delta_bis = 0, previous_section_delta = 0;
    float previous_delta_diff = 0, previous_section_delta_diff = 0;
    unsigned int horizon_y = m_backend.screenHeight/2;
    unsigned int previous_section_screen_y = m_backend.screenHeight;
    RoadSection previous_section;


    for (unsigned int i = m_backend.screenHeight-1; i >= horizon_y; i--) {
        int h_screen_from_ground = m_backend.screenHeight - i;
        int z_ground = cam_dist_to_screen*h_screen_from_ground / (cam_height-h_screen_from_ground);
        int z_ground_absolute = z_ground + z_advance;
        RoadSection section = LevelUtil::findRoadSection(level, z_ground_absolute);
        if (previous_section.z_begin != section.z_begin) {
            previous_section = section;
            previous_section_delta = previous_delta;
            previous_section_delta_diff = previous_delta_diff;
            previous_section_screen_y = i+1;
        }

        previous_delta_bis = previous_delta;
        previous_delta = draw_ground_line(level, section, z_advance, z_ground, i, previous_section_delta, previous_section_delta_diff, previous_section_screen_y);
        previous_delta_diff = previous_delta - previous_delta_bis;
    }
}

int Renderer::get_screeny_from_zground(const unsigned int &z_ground) {
    return m_backend.screenHeight - z_ground*cam_height/(z_ground+cam_dist_to_screen);
}

float Renderer::draw_ground_line(const Level& level, const RoadSection &section, const unsigned int &z_advance, const int &z_ground, const unsigned int &screen_y,
                                      const float &previous_section_delta, const float& previous_section_delta_diff, const unsigned int &previous_section_screen_y) {
    int z_ground_absolute = z_ground + z_advance;
    int road_width = lane_width * level.nb_lanes;
    int w = road_width - road_width*z_ground / (z_ground + cam_dist_to_screen);
    BackColor grass_color = z_ground_absolute % 150 < 75 ? GREEN : LIGHTGREEN;

    m_backend.draw_rectangle(0, screen_y, m_backend.screenWidth, 1, grass_color);

    int z_begin_section = z_ground_absolute - std::max(section.z_begin, z_advance);
    float delta = previous_section_delta;
    delta += previous_section_delta_diff * (previous_section_screen_y - screen_y);

    delta += (float)section.angle*(z_begin_section*z_begin_section)/road_curve_constant;
    m_backend.draw_rectangle((m_backend.screenWidth-w)/2+delta, screen_y, w, 1, GRAY);

    // Draw lanes
    if (z_ground_absolute % 80 < 30) {
        for (unsigned int i=0; i<level.nb_lanes-1; i++) {
            int draw_lane_delta = (i+1) * w / level.nb_lanes -w/2;

            int w_middle = (float)w*0.1/level.nb_lanes;
            m_backend.draw_rectangle((m_backend.screenWidth-w_middle)/2+delta+draw_lane_delta, screen_y, w_middle, 1, WHITE);
        }

    }

    return delta;
}
