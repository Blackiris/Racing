#include <iostream>

#include "Backend/raylib_backend.h"
#include "car.h"
#include "level.h"
#include "raylib.h"

using namespace std;

void drawScreen(const int screenWidth, const int screenHeight, Texture2D &carTexture)
{
    BeginDrawing();

    ClearBackground(SKYBLUE);
    DrawText("Congrats! You created your first window!", 150, 200, 20, LIGHTGRAY);
    DrawRectangle(screenWidth / 4 * 2 - 60, 100, 120, 60, RED);
    DrawTexture(carTexture, screenWidth/2 - carTexture.width/2, screenHeight/2 - carTexture.height/2, WHITE);


    EndDrawing();
}

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    RayLibBackend backend = RayLibBackend();
    backend.init_window(screenWidth, screenHeight);
    Sprite car_sprite = Sprite(50, 400, "resources/car.png");
    std::list<Sprite*> sprites = {&car_sprite};
    car_sprite.x = 80;

    Car car = Car();
    Level level = Level({
        RoadSection(000, 0),
        RoadSection(300, 2),
        RoadSection(1000, 0),
        RoadSection(1500, -3),
        RoadSection(1800, 0),
        RoadSection(2500, 1),
    });

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_LEFT)) {
            car.add_xdelta(-2);
        }
        if (IsKeyDown(KEY_RIGHT)) {
            car.add_xdelta(2);
        }

        if (IsKeyDown(KEY_UP)) {
            car.add_yspeed(1);
        }
        if (IsKeyDown(KEY_DOWN)) {
            car.add_yspeed(-1);
        }
        car.update_yadvance();

        car_sprite.x = screenWidth/2 + car.get_xdelta() - car.get_width();

        backend.begin_draw();
        backend.draw_back_sprites(car.get_yadvance(), level, sprites);
        backend.draw_car_info(car);
        backend.end_draw();
    }


    backend.close();
    return 0;
}
