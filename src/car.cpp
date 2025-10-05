#include "car.h"


Car::Car(std::string image) noexcept: x_delta(0), z_advance_cm(1000), z_speed(0), m_image(image), width(80), height(41) {}
Car::Car(std::string image, const int &z_speed, const int &z_advance_cm, const float &xdelta) noexcept: x_delta(xdelta), z_advance_cm(z_advance_cm), z_speed(z_speed), m_image(image), width(80), height(41) {}



std::string Car::get_image() const {
    return m_image;
}

void Car::add_xdelta(const float& to_add) {
    x_delta += to_add;
}

float Car::get_zspeed() const noexcept {
    return z_speed;
}

void Car::add_zspeed(const float& to_add) {
    z_speed += to_add;
    if (z_speed < 0) {
        z_speed = 0;
    }
}

unsigned int Car::get_zadvance_m() const noexcept {
    return z_advance_cm/100;
}

void Car::update_zadvance() {
    z_advance_cm += z_speed;
}

int Car::get_width() const noexcept {
    return width;
}

int Car::get_height() const noexcept {
    return height;
}
