#ifndef CAR_H
#define CAR_H

class Car
{
public:
    Car();
    int get_xdelta() const;
    void add_xdelta(int to_add);
    unsigned int get_yadvance() const;
    int get_yspeed() const;
    void add_yspeed(int to_add);
    void update_yadvance();
    int get_width() const ;

private:
    int x_delta;
    unsigned int y_advance;
    int y_speed;
    int width;
};

#endif // CAR_H
