
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
    Sprite car_sprite = Sprite(50, 400, "resources/car.png");
    std::list<Sprite*> sprites = {&car_sprite};

    Car car = Car();
    Level level = Level(4, {
        RoadSection(000, 0),
        RoadSection(300, 2),
        RoadSection(1000, 0),
        RoadSection(1500, -3),
        RoadSection(1800, 0),
        RoadSection(2500, 1),
    });

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
            car.add_zspeed(-1);
        }
        RoadSection roadSection = LevelUtil::findRoadSection(level, car.get_zadvance());
        car.add_xdelta((float)-roadSection.angle*car.get_zspeed()/500);
        car.update_zadvance();

        car_sprite.x = screenWidth/2 + car.get_xdelta() - car.get_width();

        backend.begin_draw();
        renderer.draw_ground(level, car.get_zadvance());
        backend.draw_sprites(sprites);
        backend.draw_car_info(car);
        backend.end_draw();
    }


    backend.close();
    return 0;
}
