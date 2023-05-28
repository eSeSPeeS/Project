#include "bullet.h"

void Bullet::setSpeed(double x, double y)
{
    v_x=x;
    v_y=y;
}
int Bullet::getSpeed_x()
{
    return v_x;
}
int Bullet::getSpeed_y()
{
    return v_y;
}
