#include "raylib_backend.h"

RayLibBackend::RayLibBackend() {}

int cam_dist_to_screen = 50;
int max_dist_display_road = 600;
int cam_height;
int road_width = 300;
int road_curve_constant = 5000;


void RayLibBackend::init_window(const int &screenWidth, const int &screenHeight) {
    InitWindow(screenWidth, screenHeight, "Racing");
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    SetTargetFPS(60);

    cam_height = (cam_dist_to_screen+max_dist_display_road) * (screenHeight/2)/max_dist_display_road;
}

void RayLibBackend::begin_draw() {
    BeginDrawing();
}

void RayLibBackend::end_draw() {
    EndDrawing();
}

void RayLibBackend::close() {
    CloseWindow();
}


void RayLibBackend::draw_back_sprites(const unsigned int &y_advance, const Level& level, std::list<Sprite*> sprites) {
    ClearBackground(SKYBLUE);

    draw_ground(level, y_advance);

    // draw sprites
    for (Sprite* sprite: sprites) {
        DrawTexture(getTexture(sprite->image), sprite->x, sprite->y, WHITE);
    }
}

void RayLibBackend::draw_car_info(const Car& car) {
    DrawText(("Speed: " + std::to_string(car.get_yspeed())).c_str(), 50, 20, 20, LIGHTGRAY);
}

void RayLibBackend::draw_ground(const Level& level, const unsigned int &z_advance) {
    float previous_delta = 0, previous_delta_bis = 0, previous_section_delta = 0;
    float previous_delta_diff = 0, previous_section_delta_diff = 0;
    unsigned int horizon_y = screenHeight/2;
    unsigned int previous_section_screen_y = screenHeight;
    RoadSection previous_section;

    DrawRectangle(0, horizon_y, screenWidth, screenHeight-horizon_y, GREEN);
    for (unsigned int i = screenHeight-1; i >= horizon_y; i--) {
        int h_screen_from_ground = screenHeight - i;
        int z_ground = cam_dist_to_screen*h_screen_from_ground / (cam_height-h_screen_from_ground);
        int z_ground_absolute = z_ground + z_advance;
        RoadSection section = findRoadSection(level, z_ground_absolute);
        if (previous_section.z_begin != section.z_begin) {
            previous_section = section;
            previous_section_delta = previous_delta;
            previous_section_delta_diff = previous_delta_diff;
            previous_section_screen_y = i+1;
        }

        previous_delta_bis = previous_delta;
        previous_delta = draw_ground_line(section, z_advance, z_ground, i, previous_section_delta, previous_section_delta_diff, previous_section_screen_y);
        previous_delta_diff = previous_delta - previous_delta_bis;
    }
}

float RayLibBackend::draw_ground_line(const RoadSection &section, const unsigned int &z_advance, const int &z_ground, const unsigned int &screen_y,
                                    const float &previous_section_delta, const float& previous_section_delta_diff, const unsigned int &previous_section_screen_y) {
    int z_ground_absolute = z_ground + z_advance;
    int w = road_width - road_width*z_ground / (z_ground + cam_dist_to_screen);
    Color road_color = z_ground_absolute % 80 < 40 ? LIGHTGRAY : GRAY;



    int z_begin_section = z_ground_absolute - std::max(section.z_begin, z_advance);
    float delta = previous_section_delta;
    delta += previous_section_delta_diff * (previous_section_screen_y - screen_y);

    delta += (float)section.angle*(z_begin_section*z_begin_section)/road_curve_constant;
    DrawRectangle((screenWidth-w)/2+delta, screen_y, w, 1, road_color);

    return delta;
}

RoadSection RayLibBackend::findRoadSection(const Level &level, const unsigned int &z) {
    RoadSection section = level.road_sections.front();
    for (RoadSection current_section : level.road_sections) {
        if (current_section.z_begin > z) {
            break;
        }
        section = current_section;
    }
    return section;
}

Texture2D RayLibBackend::getTexture(const std::string &path) {
    if (pathToTexture.contains(path)) {
        return pathToTexture[path];
    } else {
        Texture2D texture2D = LoadTexture(path.c_str());
        pathToTexture.insert({path, texture2D});
        return texture2D;
    }
}
