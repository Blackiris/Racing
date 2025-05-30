#include "car.h"




std::string Car::get_image() const {
    return m_image;
}

void Car::add_xdelta(float to_add) {
    x_delta += to_add;
}

float Car::get_zspeed() const {
    return z_speed;
}

void Car::add_zspeed(float to_add) {
    z_speed += to_add;
    if (z_speed < 0) {
        z_speed = 0;
    }
}

unsigned int Car::get_zadvance_m() const {
    return z_advance_cm/100;
}

void Car::update_zadvance() {
    z_advance_cm += z_speed;
}

int Car::get_width() const {
    return width;
}

int Car::get_height() const {
    return height;
}
