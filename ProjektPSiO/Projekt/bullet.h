#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
class Bullet :  public sf::Sprite
{
private:
    double v_x=0;
    double v_y=0;
    float szerokosc_okna=0;
    float wysokosc_okna=0;

public:
    Bullet(int bullet_number, double V_x) {v_x=V_x;}
    ~Bullet(){}

    void setSpeed(double x, double y);
    int getSpeed_x();
    int getSpeed_y();
};

#endif // BULLET_H
