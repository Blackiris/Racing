#ifndef CAR_H
#define CAR_H

#include <string>

class Car
{
public:
    Car(std::string image): x_delta(0), z_advance_cm(1000), z_speed(0), m_image(image), width(80), height(41) {}
    Car(std::string image, const int &z_speed, const int &z_advance_cm, const float &xdelta): x_delta(xdelta), z_advance_cm(z_advance_cm), z_speed(z_speed), m_image(image), width(80), height(41) {}
    std::string get_image() const;
    void add_xdelta(const float& to_add);
    unsigned int get_zadvance_m() const;
    float get_zspeed() const;
    void add_zspeed(const float& to_add);
    void update_zadvance();
    int get_width() const;
    int get_height() const;

    float x_delta;
    unsigned int z_advance_cm;
    float z_speed;

private:
    std::string m_image;



    int width, height;
};

#endif // CAR_H
