#ifndef CAR_H
#define CAR_H

#include <string>

class Car
{
public:
    Car(std::string image) noexcept;
    Car(std::string image, const int &z_speed, const int &z_advance_cm, const float &xdelta) noexcept;
    std::string get_image() const;
    void add_xdelta(const float& to_add);
    [[nodiscard]] unsigned int get_zadvance_m() const noexcept;
    [[nodiscard]] float get_zspeed() const noexcept;
    void add_zspeed(const float& to_add);
    void update_zadvance();
    [[nodiscard]] int get_width() const noexcept;
    [[nodiscard]] int get_height() const noexcept;

    float x_delta;
    unsigned int z_advance_cm;
    float z_speed;

private:
    std::string m_image;
    int width, height;
};

#endif // CAR_H
