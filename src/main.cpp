
#include "Backend/raylib_backend.h"
#include "racing_lib/car.h"
#include "racing_lib/level.h"
#include "racing_lib/levelutil.h"
#include "racing_lib/renderer.h"
#include <format>


void manage_npcs(const Level &level,
                 const int lane_width,
                 const Car &car,
                 std::list<Car> &npcs,
                 const int max_npc_distance,
                 const unsigned max_nb_npcs,
                 const int road_width) {
    if (npcs.size() < max_nb_npcs && rand() % 100 < 3) {
        int lane_nb = rand() % level.nb_lanes;
        npcs.push_back(Car("resources/car_npc.png",
                              400 + rand() % 100,
                              (car.get_zadvance_m() + max_npc_distance - rand() % 100) * 100,
                              (-road_width + lane_width) / 2 + lane_nb * lane_width));
    }
}

Level load_level() {
    return Level(4, 10000, {
           RoadSection(000, 0),
           RoadSection(300, 2),
           RoadSection(1000, 0),
           RoadSection(1500, -3),
           RoadSection(1800, 0),
           RoadSection(2500, 1),
           RoadSection(3500, 4),
           RoadSection(4000, 0),
           RoadSection(6000, -2),
           RoadSection(7000, 0),
       });
}

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 480;
    const int lane_width = 150;
    const int max_npc_distance = 700;
    const int min_npc_distance = -200;
    const int max_nb_npcs = 5;
    const float coeff_wind = 0.000001;
    const float coeff_grass = 0.00004;

    RayLibBackend backend = RayLibBackend();
    backend.init_window(screenWidth, screenHeight);
    Renderer renderer = Renderer(backend);

    Car car("resources/car.png");
    const Level level = load_level();

    std::list<Car> npcs;


    const int road_width = lane_width * level.nb_lanes;

    float begin_time = backend.get_time();
    float current_time, final_time;
    bool win = false;


    // Main game loop
    while (!backend.should_close())    // Detect window close button or ESC key
    {
        // Check win status
        current_time = backend.get_time();
        if (!win && car.get_zadvance_m() >= level.end_line_z) {
            win = true;
            final_time = current_time - begin_time;
        }

        if (backend.isKeyDown(LEFT)) {
            car.add_xdelta(-3);
        }
        if (backend.isKeyDown(RIGHT)) {
            car.add_xdelta(3);
        }

        if (backend.isKeyDown(UP)) {
            car.add_zspeed(1);
        }
        if (backend.isKeyDown(DOWN)) {
            car.add_zspeed(-3);
        }

        // Curve
        RoadSection roadSection = LevelUtil::find_road_section(level, car.get_zadvance_m());
        car.add_xdelta((float)-roadSection.angle*car.get_zspeed()/500);
        car.update_zadvance();

        // Wind
        float current_zspeed = car.get_zspeed();
        car.add_zspeed(-coeff_wind*current_zspeed*current_zspeed);

        // Grass
        if (std::abs(car.x_delta) > road_width / 2 + 10) {
            car.add_zspeed(-coeff_grass*current_zspeed*current_zspeed);
        }


        // NPC

        // Spawn NPC
        manage_npcs(level, lane_width, car, npcs, max_npc_distance, max_nb_npcs, road_width);
        npcs.remove_if([&car](auto npc){
            long diff = (long)npc.get_zadvance_m()-car.get_zadvance_m();
            return diff > max_npc_distance || diff < min_npc_distance;
        });

        for (auto& npc: npcs) {
            npc.z_advance_cm += npc.get_zspeed();

            // Check collision
            long diff_z = npc.get_zadvance_m() - car.get_zadvance_m();
            int diff_x = std::abs(npc.x_delta - car.x_delta);
            if (npc.get_zadvance_m() - car.get_zadvance_m()) {
                if (diff_z > -15 && diff_z < 15 && diff_x < (npc.width + car.width)/2) {
                    car.add_zspeed(-50);
                }
            }
        }

        std::list<Car*> all_cars({&car});
        for (auto& npc: npcs) {
            all_cars.push_back(&npc);
        }

        backend.begin_draw();
        renderer.draw(level, all_cars, car.get_zadvance_m()-10, lane_width);
        renderer.draw_car_info(car);
        std::string time_txt = "Time: " + std::format("{:.2f}", win ? final_time : current_time-begin_time) + " s";
        backend.draw_text(time_txt, 400, 20, 20);

        if (win) {
            backend.draw_text("You win!", 300, 200, 20);
        }
        backend.end_draw();
    }


    backend.close();
    return 0;
}
