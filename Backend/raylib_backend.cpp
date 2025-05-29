#include "raylib_backend.h"

RayLibBackend::RayLibBackend() {}



void RayLibBackend::init_window(const int &screenWidth, const int &screenHeight) {
    InitWindow(screenWidth, screenHeight, "Racing");
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    SetTargetFPS(60);
}

bool RayLibBackend::should_close() {
    return WindowShouldClose();
}

void RayLibBackend::begin_draw() {
    BeginDrawing();
}

void RayLibBackend::end_draw() {
    EndDrawing();
}

void RayLibBackend::clear_background() {
    ClearBackground(SKYBLUE);
}

void RayLibBackend::close() {
    CloseWindow();
}


void RayLibBackend::draw_sprites(std::list<Sprite*> sprites) {
    for (Sprite* sprite: sprites) {
        draw_sprite(sprite);
    }
}

void RayLibBackend::draw_sprite(const Sprite* sprite) {
    DrawTexture(getTexture(sprite->image), sprite->x, sprite->y, WHITE);
}

void RayLibBackend::draw_rectangle(int posX, int posY, int width, int height, BackColor color) {
    DrawRectangle(posX, posY, width, height, Color(color.r, color.g, color.b, color.a));
}

void RayLibBackend::draw_car_info(const Car& car) {
    DrawText(("Speed: " + std::to_string(car.get_zspeed())).c_str(), 50, 20, 20, LIGHTGRAY);
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

bool RayLibBackend::isKeyDown(const KeyName &keyname) {
    bool res = false;
    switch(keyname) {
    case UP:
        res = IsKeyDown(KEY_UP);
        break;
    case DOWN:
        res = IsKeyDown(KEY_DOWN);
        break;
    case LEFT:
        res = IsKeyDown(KEY_LEFT);
        break;
    case RIGHT:
        res = IsKeyDown(KEY_RIGHT);
        break;
    }

    return res;
}
