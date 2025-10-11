#pragma once

#include <string>

class Car
{
public:
    explicit Car(const std::string& image) noexcept;
    Car(const std::string& image, const int &z_speed, const int &z_advance_cm, const float &xdelta) noexcept;
    [[nodiscard]] std::string get_image() const;
    void add_xdelta(const float& to_add);
    [[nodiscard]] unsigned int get_zadvance_m() const noexcept;
    [[nodiscard]] float get_zspeed() const noexcept;
    void add_zspeed(const float& to_add);
    void update_zadvance();

    float x_delta;
    unsigned int z_advance_cm;
    float z_speed;
    int width, height;

private:
    std::string m_image;

};
