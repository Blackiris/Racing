
#include "Backend/raylib_backend.h"
#include "car.h"
#include "level.h"
#include "levelutil.h"
#include "renderer.h"

using namespace std;


int main()
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    RayLibBackend backend = RayLibBackend();
    backend.init_window(screenWidth, screenHeight);
    Renderer renderer = Renderer(backend);

    Car car("resources/car.png");
    Level level = Level(4, {
        RoadSection(000, 0),
        RoadSection(300, 2),
        RoadSection(1000, 0),
        RoadSection(1500, -3),
        RoadSection(1800, 0),
        RoadSection(2500, 1),
    });

    Car car_npc("resources/car_npc.png");
    car_npc.z_speed = 300;
    car_npc.z_advance_cm = 10;
    car_npc.x_delta = 70;

    // Main game loop
    while (!backend.should_close())    // Detect window close button or ESC key
    {
        if (backend.isKeyDown(LEFT)) {
            car.add_xdelta(-2);
        }
        if (backend.isKeyDown(RIGHT)) {
            car.add_xdelta(2);
        }

        if (backend.isKeyDown(UP)) {
            car.add_zspeed(1);
        }
        if (backend.isKeyDown(DOWN)) {
            car.add_zspeed(-3);
        }
        RoadSection roadSection = LevelUtil::findRoadSection(level, car.get_zadvance_m());
        car.add_xdelta((float)-roadSection.angle*car.get_zspeed()/500);
        car.update_zadvance();


        // NPC
        car_npc.z_advance_cm += car_npc.get_zspeed();


        backend.begin_draw();
        renderer.draw(level, {car, car_npc}, car.get_zadvance_m()-10);
        backend.draw_car_info(car);
        backend.end_draw();
    }


    backend.close();
    return 0;
}
