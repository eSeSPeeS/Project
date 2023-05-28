#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#pragma once
#include <iostream>
#include <string>
#include "things.h"
#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Sprite {
private:
    std::vector<sf::IntRect> frames_;
    std::vector<sf::IntRect>::iterator current_frame_ = frames_.begin();
//    size_t current_frame_ = 0;
    float elapsed_accumulator_ = 0;
    float fps = 4;
    float szerokosc_okna=0;
    float wysokosc_okna=0;
    double v_x=0;
    double v_y=0;
    bool direction=true;
    double actual_position_x=214.5;
    sf::Sprite sprite;
    int t=0,t_b=0, y=0,niewazna_zmienna=0;
public:
    AnimatedSprite() : sf::Sprite(){}
    AnimatedSprite(sf::Texture textura){sprite.setTexture(textura);}
    AnimatedSprite(sf::Sprite cosiek){sprite=cosiek;}
    void add_animation_frame(const sf::IntRect &frame);
    void step(const sf::Time &elapsed);
    void setSpeed(double speed_x, double speed_y);
    double getSpeed_x();
    double getSpeed_y();
//    bool getPiotrowiL();
//    bool getPiotrowiP();
//    void setPiotrowiL(bool x);
//    void setPiotrowiP(bool x);
    void mowe(const sf::Time &elapsed, int v_xa, int v_ya);
    void SetPozycja(double x, double y);
    void setBounds(float x, float y);
    void B1(const sf::Time &elapsed, const std::vector<AnimatedSprite> walls);
    void Bounds(const sf::Time &elapsed, const std::vector<Things> walls);
    void setDirection(bool s);
    bool getDirection();
    sf::FloatRect polozenie();
    void set_actual_position(sf::Time elapsed, double v);
    double get_actual_position();
    void animate(const sf::Time &elapsed);
    void animate2(const sf::Time &elapsed, const std::vector<Things> walls,bool Piotrowi_zle_w_prawo, bool Piotrowi_zle_w_lewo);
    void jump(const sf::Time &elapsed);
    void gravity(const sf::Time &elapsed, std::vector<Things> walls, const sf::FloatRect ludzik_bounds);
    void bieganie(bool Piotrowi_zle_w_prawo, bool Piotrowi_zle_w_lewo);
    void bounce(float window_width,sf::Time elapsed);
    void toLeft(sf::Time elapsed);
    void toRight(sf::Time elapsed);
    void toUp(sf::Time elapsed);
    void toDown(sf::Time elapsed);

};

sf::Texture loadTexture(const std::string &filename_with_path);

#endif // ANIMATEDSPRITE_H
