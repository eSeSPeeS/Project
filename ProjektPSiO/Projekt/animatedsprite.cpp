#include "animatedsprite.h"

#include <iostream>

void AnimatedSprite::add_animation_frame(const sf::IntRect &frame) {
    frames_.emplace_back(frame);
    current_frame_ = frames_.begin();
}

void AnimatedSprite::step(const sf::Time &elapsed) {
    elapsed_accumulator_ += elapsed.asSeconds();

    while (elapsed_accumulator_ >= 1.0/fps) {
        elapsed_accumulator_ -= 1.0/fps;
        if (!frames_.empty()) {
//                setTextureRect(frames_[current_frame_]);
//                current_frame_ = (current_frame_ + 1) % frames_.size();
            setTextureRect(*current_frame_);
            current_frame_++;
            if(current_frame_ == frames_.end())
            {
                current_frame_ = frames_.begin();
            }
        }
    }
}

//bool AnimatedSprite::getPiotrowiL(){
//    return Piotrowi_zle_w_lewo;
//}
//bool AnimatedSprite::getPiotrowiP(){
//    return Piotrowi_zle_w_prawo;
//}
//void AnimatedSprite::setPiotrowiL(bool x){
//    Piotrowi_zle_w_lewo=x;
//};
//void AnimatedSprite::setPiotrowiP(bool x){
//    Piotrowi_zle_w_prawo=x;
//};

void AnimatedSprite::setSpeed(double speed_x, double speed_y){
    v_x = speed_x;
    v_y = speed_y;
}

double AnimatedSprite::getSpeed_x(){
    return v_x;
}

double AnimatedSprite::getSpeed_y(){
    return v_y;
}

void AnimatedSprite::animate(const sf::Time &elapsed) {   // zerowanie prędkości pionowej
    move(v_x*elapsed.asSeconds(),v_y*elapsed.asSeconds());
}

void AnimatedSprite::jump(const sf::Time &elapsed) {
    move(50*v_x*elapsed.asSeconds(),-50*std::abs(v_x)*elapsed.asSeconds());
}

void AnimatedSprite::gravity(const sf::Time &elapsed, std::vector<Things> walls, const sf::FloatRect ludzik_bounds)
    {
        if(v_y>0&&polozenie().top+polozenie().height<900)
        {
            v_y=v_y+elapsed.asMilliseconds()*2;
        }
        if(v_y<0)
        {
            v_y=v_y+elapsed.asMilliseconds()*2;
        }
        if(std::abs(v_y) == 0)
        {
            for (unsigned int i = 0; i < walls.size(); i++) {
                sf::FloatRect walls_bounds = walls[i].polozenie();
                if (ludzik_bounds.top + ludzik_bounds.height >= walls_bounds.top &&
                        ludzik_bounds.top + ludzik_bounds.height <= walls_bounds.top + walls_bounds.height &&
                        ludzik_bounds.left + ludzik_bounds.width - 10 >= walls_bounds.left &&
                        ludzik_bounds.left + 10 <= walls_bounds.left + walls_bounds.width)
                {
                    v_y=0;
                    break;
                }
                else
                {
                    v_y=1;
                }
            }
        }
    }

sf::Texture loadTexture(const std::string &filename_with_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename_with_path)) {
        std::cerr << "Could not load texture" << std::endl;
    }
    return texture;
}

void AnimatedSprite::bounce(float window_width, sf::Time elapsed)    // implementacja zderzeń z granicami obszaru
{
    sf::FloatRect hero_bounds = getGlobalBounds();

    if(hero_bounds.left <= 0)
    {
          toRight(elapsed);
    }
    if(hero_bounds.left+hero_bounds.width >= window_width)
    {
          toLeft(elapsed);
    }
}

void AnimatedSprite::toLeft(sf::Time elapsed)
    {
        move(-350*elapsed.asSeconds(),0);
        setScale(-4.f,4.f);
    }

void AnimatedSprite::toRight(sf::Time elapsed)
     {
       move(350*elapsed.asSeconds(),0);
       setScale(4.f,4.f);
     }


void AnimatedSprite::toUp(sf::Time elapsed)
     {
        move(0,-350*elapsed.asSeconds());
     }

void AnimatedSprite::toDown(sf::Time elapsed)
     {
        move(0,350*elapsed.asSeconds());
     }

    void AnimatedSprite::SetPozycja(double x, double y)
    {
        sprite.setPosition(x,y);
    }
    void AnimatedSprite::set_actual_position(sf::Time elapsed, double v)
    {
        actual_position_x=actual_position_x+v*elapsed.asSeconds();
    }
    double AnimatedSprite::get_actual_position()
    {
        return actual_position_x;
    }
    void AnimatedSprite::setBounds(float x, float y)
    {
        szerokosc_okna=x;
        wysokosc_okna=y;
    }
    void AnimatedSprite::B1(const sf::Time &elapsed, const std::vector<AnimatedSprite> walls)
    {
        sf::FloatRect rectangle_bounds = sprite.getGlobalBounds();
        if(rectangle_bounds.top>=0)
        {
            sprite.move(0, -300*elapsed.asSeconds());
        }
    }
    void AnimatedSprite::setDirection(bool s)
      {
          direction=s;
      }
      bool AnimatedSprite::getDirection()
      {
          return direction;
      }
      sf::FloatRect AnimatedSprite::polozenie()
      {
          return sprite.getGlobalBounds();
      }
    void AnimatedSprite::Bounds(const sf::Time &elapsed, const std::vector<Things> walls)
        {
            sf::FloatRect ludzik_bounds = sprite.getGlobalBounds();

            if(ludzik_bounds.left+ludzik_bounds.width>=szerokosc_okna)
            {
                v_x=std::abs(v_x)*(-1);
            }

            if(ludzik_bounds.top+ludzik_bounds.height>=wysokosc_okna)
            {
                v_y=std::abs(v_y)*(-1);
            }

            if(ludzik_bounds.left<=0)
            {
                v_x=std::abs(v_x);
            }

            if(ludzik_bounds.top<=0)
            {
                v_y=std::abs(v_y);
            }

        }
    void AnimatedSprite::mowe(const sf::Time &elapsed, int v_xa, int v_ya)
    {
        sprite.move(v_xa*elapsed.asSeconds(), v_ya*elapsed.asSeconds());
    }
    void AnimatedSprite::bieganie(bool Piotrowi_zle_w_prawo, bool Piotrowi_zle_w_lewo)
        {

            if(niewazna_zmienna==0)
            {
                sprite.setPosition(240, 400);
                niewazna_zmienna=1;
            }

            if(v_x>0||Piotrowi_zle_w_prawo==1)
            {
                sprite.setScale(1.5, 1.5);
                if(t==40)
                {
                    sf::Vector2f w(y, 0);
                    sf::IntRect rect(w.x, w.y, 34, 41);
                    sprite.setTextureRect(rect);
                    y=y+35;
                    if(y==490)
                    {
                        y=0;
                    }
                    t=0;
                }
                t=t+1;
            }
            else if(v_x<0||Piotrowi_zle_w_lewo==1)
            {
                sprite.setScale(-1.5, 1.5);
                if(t==40)
                {
                    sf::Vector2f w(y, 0);
                    sf::IntRect rect(w.x, w.y, 34, 41);
                    sprite.setTextureRect(rect);
                    y=y+35;
                    if(y==490)
                    {
                        y=0;
                    }
                    t=0;
                }
                t=t+1;
            }
            else
            {
                sf::Vector2f w(0, 0);
                sf::IntRect rect(w.x, w.y, 34, 41);
                sprite.setTextureRect(rect);
            }

        }
    void AnimatedSprite::animate2(const sf::Time &elapsed, const std::vector<Things> walls,bool Piotrowi_zle_w_prawo, bool Piotrowi_zle_w_lewo)
        {

            sf::FloatRect ludzik_bounds = sprite.getGlobalBounds();

            gravity(elapsed, walls, ludzik_bounds);
            Bounds(elapsed, walls);
            sprite.move(v_x*elapsed.asSeconds(), v_y*elapsed.asSeconds());
            //sprite.rotate(v_o*elapsed.asSeconds());
            bieganie(Piotrowi_zle_w_prawo, Piotrowi_zle_w_lewo);
        }
