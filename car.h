#ifndef CAR_H
#define CAR_H

class Car
{
public:
    Car();
    int get_xdelta() const;
    void add_xdelta(int to_add);
    unsigned int get_zadvance() const;
    int get_zspeed() const;
    void add_zspeed(int to_add);
    void update_zadvance();
    int get_width() const ;

private:
    int x_delta;
    unsigned int z_advance;
    int z_speed;
    int width;
};

#endif // CAR_H
