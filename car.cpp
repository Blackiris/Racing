#include "car.h"

Car::Car(): x_delta(0), z_advance(0), z_speed(0), width(30) {}

int Car::get_xdelta() const {
    return x_delta;
}

void Car::add_xdelta(int to_add) {
    x_delta += to_add;
}

int Car::get_zspeed() const {
    return z_speed;
}

void Car::add_zspeed(int to_add) {
    z_speed += to_add;
    if (z_speed < 0) {
        z_speed = 0;
    }
}

unsigned int Car::get_zadvance() const {
    return z_advance/10;
}

void Car::update_zadvance() {
    z_advance += z_speed;
}

int Car::get_width() const {
    return width;
}
