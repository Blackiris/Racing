#include "renderer.h"
#include "levelutil.h"

int cam_dist_to_screen = 50;
int max_dist_display_road = 600;
int cam_height;
int road_curve_constant = 5000;



Renderer::Renderer(IBackend &backend): m_backend(backend) {
    cam_height = (cam_dist_to_screen+max_dist_display_road) * (backend.screenHeight/2)/max_dist_display_road;
}

void Renderer::draw(const Level& level, std::list<Car> cars, const unsigned int &cam_z_advance, const int &lane_width) {
    std::map<int, float> road_deltas = compute_road_deltas(level, cam_z_advance);
    draw_ground(level, cam_z_advance, road_deltas, lane_width);
    draw_cars(cars, cam_z_advance, road_deltas);
}

void Renderer::draw_cars(std::list<Car> cars, const unsigned int &cam_z_advance, const std::map<int, float> &road_deltas) {
    std::list<Car> z_ordered_cars = cars;
    z_ordered_cars.sort( []( const Car &a, const Car &b ) { return a.z_advance_cm > b.z_advance_cm; } );
    for (Car car : z_ordered_cars) {
        draw_car(car, cam_z_advance, road_deltas);
    }
}

void Renderer::draw_car(Car car, const unsigned int &cam_z_advance, const std::map<int, float> &road_deltas) {
    int z_ground = car.get_zadvance_m() - cam_z_advance;
    if (z_ground > 0 && z_ground<max_dist_display_road) {
        int screen_y = get_screeny_from_zground(car.get_zadvance_m() - cam_z_advance);
        float scale = get_scale_from_zground(car.get_zadvance_m() - cam_z_advance);
        Sprite car_sprite = Sprite(m_backend.screenWidth/2 + (car.x_delta - car.get_width()/2)*scale + road_deltas.at(screen_y),
                                   screen_y-car.get_height()*scale, car.get_image(), scale);
        m_backend.draw_sprite(&car_sprite);
    }
}

std::map<int, float> Renderer::compute_road_deltas(const Level& level, const unsigned int &cam_z_advance) {
    float road_delta = 0, previous_delta = 0, previous_section_delta = 0;
    float previous_delta_diff = 0, previous_section_delta_diff = 0;

    unsigned int horizon_y = m_backend.screenHeight/2;
    unsigned int previous_section_screen_y = m_backend.screenHeight;
    RoadSection previous_section;

    std::map<int, float> road_deltas;

    for (unsigned int i = m_backend.screenHeight-1; i >= horizon_y; i--) {
        int h_screen_from_ground = m_backend.screenHeight - i;
        int z_ground = cam_dist_to_screen*h_screen_from_ground / (cam_height-h_screen_from_ground);
        int z_ground_absolute = z_ground + cam_z_advance;
        RoadSection section = LevelUtil::findRoadSection(level, z_ground_absolute);
        if (previous_section.z_begin != section.z_begin) {
            previous_section = section;
            previous_section_delta = road_delta;
            previous_section_delta_diff = previous_delta_diff;
            previous_section_screen_y = i+1;
        }

        previous_delta = road_delta;


        road_delta = previous_section_delta;
        int z_begin_section = z_ground_absolute - std::max(section.z_begin, cam_z_advance);

        road_delta += previous_section_delta_diff * (previous_section_screen_y - i);
        road_delta += (float)section.angle*(z_begin_section*z_begin_section)/road_curve_constant;

        road_deltas.insert({i, road_delta});

        previous_delta_diff = road_delta - previous_delta;
    }

    return road_deltas;
}

void Renderer::draw_ground(const Level& level, const unsigned int &z_advance, const std::map<int, float> &road_deltas, const int &lane_width) {
    m_backend.clear_background();

    unsigned int horizon_y = m_backend.screenHeight/2;


    for (unsigned int i = m_backend.screenHeight-1; i >= horizon_y; i--) {
        int h_screen_from_ground = m_backend.screenHeight - i;
        float z_ground = (float)cam_dist_to_screen*h_screen_from_ground / (cam_height-h_screen_from_ground);

        draw_ground_line(level, z_advance, z_ground, i, road_deltas.at(i), lane_width);
    }
}

int Renderer::get_screeny_from_zground(const float &z_ground) {
    return m_backend.screenHeight - z_ground*cam_height/(z_ground+cam_dist_to_screen);
}

float Renderer::get_scale_from_zground(const float &z_ground) {
    return 1. - (float)z_ground / (z_ground + cam_dist_to_screen);
}

void Renderer::draw_ground_line(const Level& level, const unsigned int &cam_z_advance, const float &z_ground, const unsigned int &screen_y,
                                      const float &road_delta, const int &lane_width) {
    int z_ground_absolute = z_ground + cam_z_advance;
    int road_width = lane_width * level.nb_lanes;
    int w = road_width * get_scale_from_zground(z_ground);
    BackColor grass_color = z_ground_absolute % 180 < 90 ? GREEN : LIGHTGREEN;

    m_backend.draw_rectangle(0, screen_y, m_backend.screenWidth, 1, grass_color);
    m_backend.draw_rectangle((m_backend.screenWidth-w)/2+road_delta, screen_y, w, 1, GRAY);

    // Draw lanes
    if (z_ground_absolute % 60 < 20) {
        for (unsigned int i=0; i<level.nb_lanes-1; i++) {
            int draw_lane_delta = (i+1) * w / level.nb_lanes -w/2;

            int w_middle = (float)w*0.1/level.nb_lanes;
            m_backend.draw_rectangle((m_backend.screenWidth-w_middle)/2+road_delta+draw_lane_delta, screen_y, w_middle, 1, WHITE);
        }

    }
}

void Renderer::draw_car_info(const Car& car) {
    m_backend.draw_text("Speed: " + std::to_string(car.get_zspeed()), 50, 20, 20);
}
