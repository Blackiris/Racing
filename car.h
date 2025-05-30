#ifndef CAR_H
#define CAR_H

#include <string>

class Car
{
public:
    Car(std::string image);
    std::string get_image() const;
    void add_xdelta(float to_add);
    unsigned int get_zadvance_m() const;
    int get_zspeed() const;
    void add_zspeed(int to_add);
    void update_zadvance();
    int get_width() const;
    int get_height() const;

    float x_delta;
    unsigned int z_advance_cm;
    int z_speed;

private:
    std::string m_image;



    int width, height;
};

#endif // CAR_H
