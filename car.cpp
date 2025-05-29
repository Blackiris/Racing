#include "car.h"

Car::Car(): x_delta(0), y_advance(0), y_speed(0), width(30) {}

int Car::get_xdelta() const {
    return x_delta;
}

void Car::add_xdelta(int to_add) {
    x_delta += to_add;
}

int Car::get_yspeed() const {
    return y_speed;
}

void Car::add_yspeed(int to_add) {
    y_speed += to_add;
}

unsigned int Car::get_yadvance() const {
    return y_advance;
}

void Car::update_yadvance() {
    y_advance += y_speed;
}

int Car::get_width() const {
    return width;
}
