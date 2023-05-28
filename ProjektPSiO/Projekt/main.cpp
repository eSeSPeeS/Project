#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include "animatedsprite.h"
#include "things.h"
#include "bullet.h"

using namespace std;

int main()
{   //int zmienna_do_usuniecia_bo_Piotrowi_pewnie_nie_bedzie_sie_podobalo=0;

    sf::Texture texture_space1 = loadTexture("Tekstury/planet_1_0.png");
    sf::Texture texture_space2 = loadTexture("Tekstury/planet_2_0.png");
    sf::Texture texture_space3 = loadTexture("Tekstury/planet_3_0.png");
    sf::Texture texture_hero = loadTexture("Tekstury/SpaceExplorerSheet.png");
    sf::Texture texture_wall = loadTexture("Tekstury/Wall.jpg");

    // fonts

        sf::Font font;
        if (!font.loadFromFile("Arial.ttf"))
        {
           std::cerr << "File Arial.ttf not found !" << std::endl;
        }

        sf::RenderWindow window(sf::VideoMode(1600, 900), "Projekt");
        window.setFramerateLimit(60);

        sf::Vector2u size = window.getSize();
        double window_width = size.x;
        double window_height = size.y;

        sf::Sprite hero1;
        hero1.setTexture(texture_hero);
        hero1.setOrigin(8, 8);
        hero1.setScale(3.5, 3.5);
        hero1.setTextureRect(sf::IntRect(0, 0, 16, 16));


        AnimatedSprite hero(texture_hero);
        hero.setScale(1, 1);
        hero = hero1;
        hero.SetPozycja(100, 100);
        hero.setSpeed(0, 1);
        hero.setBounds(window.getSize().x, window.getSize().y);


        std::vector<Things> walls;
        std::vector<Things> things;
        std::vector<Bullet> bullets;
        sf::Vector2f position;

        position={0.0f, 0.0f};
        things.emplace_back(things.size(), position);
        things[things.size()-1].setTexture(texture_space1);
        things[things.size()-1].setScale(1, 1);
        things[things.size()-1].setTextureRect(sf::IntRect(0, 0, 900, window_height));

        position={900.0f, 0.0f};
        things.emplace_back(things.size(), position);
        things[things.size()-1].setTexture(texture_space2);
        things[things.size()-1].setScale(1, 1);
        things[things.size()-1].setTextureRect(sf::IntRect(0, 0, 900, window_height));

        position={000.0f, 500.0f};
        walls.emplace_back(walls.size(), position);
        walls[walls.size()-1].setTexture(texture_wall);
        walls[walls.size()-1].setScale(0.5, 0.5);
        walls[walls.size()-1].setTextureRect(sf::IntRect(0, 0, 4000, 70));

    sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color::Blue);
        text.setCharacterSize(48);
        text.setStyle(sf::Text::Bold);
        text.setPosition(0.9*window_width, 0.05*window_height);

    sf::Clock clock;
    sf::Clock clock2;

    bool Piotrowi_zle_w_prawo=0;
    bool Piotrowi_zle_w_lewo=0;

    while (window.isOpen()) {
        // EVENTS
        sf::FloatRect hero_bounds=hero.polozenie();
        sf::Event event;

        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                std::cout << "Closing the window" << std::endl;
                window.close();
            }
        }

        //Rysowanie
        for (auto &obj : things) {
            window.draw(obj);
        }
        for(auto &obj : walls) {
            window.draw(obj);
        }

        window.draw(hero);

        window.draw(text);

        for (auto &obj : bullets) {
            obj.move(obj.getSpeed_x(), obj.getSpeed_y());
            window.draw(obj);
        }

        // LOGIC
        sf::Time elapsed = clock.restart();
        sf::Time reload = clock2.getElapsedTime();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    hero.setDirection(false);
                    if(hero.getSpeed_y()==0){
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.left <= walls_bounds.left + walls_bounds.width &&
                                    hero_bounds.left >= walls_bounds.left &&
                                    hero_bounds.top <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.top >= walls_bounds.top)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if (hm) {
                            hero.setSpeed(0, 0);
                        }
                        else {
                            hero.set_actual_position(elapsed, -200);
                            hero.setSpeed(-200, -700);
                        }
                    }
                    else
                    {
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                    hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                    hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if(hm)
                        {
                            hero.setSpeed(0, 0);
                        }
                        else
                        {
                            if((hero_bounds.left<1)&&hero.get_actual_position()>1)
                            {
                                Piotrowi_zle_w_lewo=1;
                                for (auto &obj : things) {
                                    obj.move(200*elapsed.asSeconds(), 0);
                                }
                                for (auto &obj : walls) {
                                    obj.move(200*elapsed.asSeconds(), 0);
                                }
                                hero.set_actual_position(elapsed, -200);
                                hero.setSpeed(0, hero.getSpeed_y());
                            }
                            else
                                if((hero.get_actual_position()>0)&&hero.getSpeed_x()!=0)
                                {
                                    hero.set_actual_position(elapsed, -200);
                                }
                            hero.setSpeed(-200, hero.getSpeed_y());
                        }
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    hero.setDirection(true);
                    if(hero.getSpeed_y()==0){
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.left + hero_bounds.width >= walls_bounds.left &&
                                    hero_bounds.left + hero_bounds.width <= walls_bounds.left + walls_bounds.width &&
                                    hero_bounds.top <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.top >= walls_bounds.top)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if (hm) {
                            hero.setSpeed(0, 0);
                        }
                        else {
                            for (unsigned int i = 0; i < walls.size(); i++) {
                                sf::FloatRect walls_bounds = walls[i].polozenie();
                                if (hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                        hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                        hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                        hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                                {
                                    hero.setSpeed(200, -700);
                                    hero.set_actual_position(elapsed, 200);
                                }
                            }
                        }
                    }
                    else
                    {
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                    hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                    hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if(hm)
                        {
                            hero.setSpeed(0, 0);
                        }
                        else
                        {
                            if(hero_bounds.left+hero_bounds.width>window.getSize().x/2)
                            {
                                Piotrowi_zle_w_prawo=1;
                                for (auto &obj : things) {
                                    obj.move(-200*elapsed.asSeconds(), 0);
                                }
                                for (auto &obj : walls) {
                                    obj.move(-200*elapsed.asSeconds(), 0);
                                }
                                hero.set_actual_position(elapsed, 200);
                                hero.setSpeed(0, hero.getSpeed_y());
                            }
                            else {
                                hero.setSpeed(200, hero.getSpeed_y());
                                hero.set_actual_position(elapsed, 200);
                            }
                        }
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    hero.setDirection(false);
                    bool hm = false;
                    for (unsigned int i = 0; i < walls.size(); i++) {
                        sf::FloatRect walls_bounds = walls[i].polozenie();
                        if (hero_bounds.left <= walls_bounds.left + walls_bounds.width &&
                                hero_bounds.left >= walls_bounds.left &&
                                hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height)
                        {
                            hm = true;
                            break;
                        }
                    }
                    if (hm) {
                        hero.setSpeed(0,0);
                    }
                    else {
                        hero.setSpeed(-200, 100);
                        hero.set_actual_position(elapsed, -200);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    hero.setDirection(true);
                    bool hm = false;
                    for (unsigned int i = 0; i < walls.size(); i++) {
                        sf::FloatRect walls_bounds = walls[i].polozenie();
                        if (hero_bounds.left + hero_bounds.width >= walls_bounds.left &&
                                hero_bounds.left + hero_bounds.width <= walls_bounds.left + walls_bounds.width &&
                                hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height)
                        {
                            hm = true;
                            break;
                        }
                    }
                    if (hm) {
                        hero.setSpeed(0, 0);
                    }
                    else {
                        hero.setSpeed(200, 100);
                    }
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    hero.setDirection(false);
                    Piotrowi_zle_w_prawo=0;
                    if(hero.getSpeed_y()==0)
                    {
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.left <= walls_bounds.left + walls_bounds.width &&
                                    hero_bounds.left >= walls_bounds.left &&
                                    hero_bounds.top + hero_bounds.height-10 >= walls_bounds.top &&
                                    hero_bounds.top+10 <= walls_bounds.top + walls_bounds.height)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if (hm) {
                            hero.setSpeed(0, 0);
                        }
                        else {
                            if((hero_bounds.left<1)&&hero.get_actual_position()>1)
                            {
                                Piotrowi_zle_w_lewo=1;
                                for (auto &obj : things) {
                                    obj.move(200*elapsed.asSeconds(), 0);
                                }
                                for (auto &obj : walls) {
                                    obj.move(200*elapsed.asSeconds(), 0);
                                }
                                if(hero.get_actual_position()>0)
                                    hero.set_actual_position(elapsed, -200);
                                hero.setSpeed(0, hero.getSpeed_y());
                            }
                            else{
                                if(hero.get_actual_position()>0)
                                    hero.set_actual_position(elapsed, -200);
                                hero.setSpeed(-200, hero.getSpeed_y());
                            }
                        }
                    }
                    else
                    {
                        bool hm=false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (
                                    hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                    hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                    hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width
                                    )
                            {
                                hm = true;
                                break;
                            }
                        }
                        if(hm)
                        {
                            hero.setSpeed(0, 0);
                        }
                        else
                            if((hero_bounds.left<1)&&(hero.get_actual_position()>1))
                            {
                                Piotrowi_zle_w_lewo=1;
                                for (auto &obj : things) {
                                    obj.move(200*elapsed.asSeconds(), 0);
                                }
                                for (auto &obj : walls) {
                                    obj.move(200*elapsed.asSeconds(), 0);
                                }
                                //hero.set_actual_position(elapsed, -200);
                                hero.setSpeed(0, hero.getSpeed_y());
                            }
                            else{
                                if(hero.getSpeed_x()!=0)
                                    hero.set_actual_position(elapsed, -200);
                                hero.setSpeed(-200, hero.getSpeed_y());
                            }
                    }
                }


                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    hero.setDirection(true);
                    Piotrowi_zle_w_lewo=0;
                    if(hero.getSpeed_y()==0)
                    {
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.left + hero_bounds.width >= walls_bounds.left &&
                                    hero_bounds.left + hero_bounds.width <= walls_bounds.left + walls_bounds.width &&
                                    hero_bounds.top + hero_bounds.height-10 >= walls_bounds.top &&
                                    hero_bounds.top+10 <= walls_bounds.top + walls_bounds.height)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if (hm) {
                            hero.setSpeed(0, hero.getSpeed_y());
                        }
                        else {
                            if(hero_bounds.left+hero_bounds.width>window.getSize().x/2&&hero_bounds.left+hero_bounds.width<5000)
                            {
                                Piotrowi_zle_w_prawo=1;
                                for (auto &obj : things) {
                                    obj.move(-200*elapsed.asSeconds(), 0);
                                }
                                for (auto &obj : walls) {
                                    obj.move(-200*elapsed.asSeconds(), 0);
                                }
                                hero.set_actual_position(elapsed, 200);
                                hero.setSpeed(0, hero.getSpeed_y());
                            }
                            else {
                                if(hero.getSpeed_x()!=0)
                                    hero.set_actual_position(elapsed, 200);
                                hero.setSpeed(200, hero.getSpeed_y());
                            }
                        }
                    }
                    else
                    {

                        bool hm=false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (
                                    hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                    hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                    hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width
                                    )
                            {
                                hm = true;
                                break;
                            }
                        }
                        if(hm)
                        {
                            hero.setSpeed(0, 0);
                        }
                        else
                        {
                            if(hero_bounds.left+hero_bounds.width>window.getSize().x/2&&hero_bounds.left+hero_bounds.width<5000)
                            {
                                Piotrowi_zle_w_prawo=1;
                                for (auto &obj : things) {
                                    obj.move(-200*elapsed.asSeconds(), 0);
                                }
                                for (auto &obj : walls) {
                                    obj.move(-200*elapsed.asSeconds(), 0);
                                }
                                hero.set_actual_position(elapsed, 200);
                                hero.setSpeed(0, hero.getSpeed_y());
                            }
                            else {

                                hero.setSpeed(200, hero.getSpeed_y());
                                if(hero.getSpeed_x()!=0)
                                    hero.set_actual_position(elapsed, 200);
                            }
                        }
                    }
                }


                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    if(hero.getSpeed_y()==0)
                    {
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.top <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.top >= walls_bounds.top &&
                                    hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                    hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if (hm) {
                            hero.setSpeed(0, 0);
                        }
                        else {
                            for (unsigned int i = 0; i < walls.size(); i++) {
                                sf::FloatRect walls_bounds = walls[i].polozenie();
                                if (hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                        hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                        hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                        hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                                {
                                    hero.setSpeed(0, -700);
                                }
                            }
                        }
                    }
                    else
                    {
                        bool hm = false;
                        for (unsigned int i = 0; i < walls.size(); i++) {
                            sf::FloatRect walls_bounds = walls[i].polozenie();
                            if (hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                    hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                    hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                    hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                            {
                                hm = true;
                                break;
                            }
                        }
                        if(hm)
                        {
                            hero.setSpeed(0, 0);
                        }
                        else
                        {
                            hero.setSpeed(0, hero.getSpeed_y());
                        }
                    }
                }


                else {
                    bool hm = false;
                    for (unsigned int i = 0; i < walls.size(); i++) {
                        sf::FloatRect walls_bounds = walls[i].polozenie();
                        if (hero_bounds.top + hero_bounds.height >= walls_bounds.top &&
                                hero_bounds.top + hero_bounds.height <= walls_bounds.top + walls_bounds.height &&
                                hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                                hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                        {
                            hm = true;
                            break;
                        }
                    }
                    if (hm) {
                        hero.setSpeed(0, 0);
                    }

                    else {
                        if(hero.getSpeed_y()!=0)
                        {
                            hero.setSpeed(0, hero.getSpeed_y());
                        }
                    }
                }
                bool hm = false;
                for (unsigned int i = 0; i < walls.size(); i++) {
                    sf::FloatRect walls_bounds = walls[i].polozenie();
                    if (hero_bounds.top <= walls_bounds.top + walls_bounds.height &&
                            hero_bounds.top >= walls_bounds.top &&
                            hero_bounds.left + hero_bounds.width-10 >= walls_bounds.left &&
                            hero_bounds.left+10 <= walls_bounds.left + walls_bounds.width)
                    {
                        hm = true;
                        break;
                    }
                }
                if(hm)
                {
                    //hero.setSpeed(hero.getSpeed_x(), abs(hero.getSpeed_y()), 0);
                    hero.setSpeed(hero.getSpeed_x(), 1);
                }

                hm = false;
                for (unsigned int i = 0; i < walls.size(); i++) {
                    sf::FloatRect walls_bounds = walls[i].polozenie();
                    if (((hero_bounds.left <= walls_bounds.left + walls_bounds.width &&
                          hero_bounds.left >= walls_bounds.left &&
                          hero_bounds.top + hero_bounds.height-10 >= walls_bounds.top &&
                          hero_bounds.top+10 <= walls_bounds.top + walls_bounds.height)||
                         (hero_bounds.left + hero_bounds.width >= walls_bounds.left &&
                          hero_bounds.left + hero_bounds.width <= walls_bounds.left + walls_bounds.width &&
                          hero_bounds.top + hero_bounds.height-10 >= walls_bounds.top &&
                          hero_bounds.top+10 <= walls_bounds.top + walls_bounds.height))&&
                            hero.getSpeed_y()!=0)
                    {
                        hm = true;
                        break;
                    }
                }
                if(hm)
                {
                    hero.setSpeed(0, hero.getSpeed_y());
                }


//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//                {
//                    // reload = clock.getElapsedTime();

//                    // Sprawdzenie, czy minęło wystarczająco czasu od ostatniego utworzenia obiektu bullet
//                    if (reload.asSeconds() >= 0.5f)
//                    {
//                        if(hero.getDirection()){
//                            bullets.emplace_back(bullets.size(), 2*elapsed.asMilliseconds());
//                            bullets[bullets.size() - 1].setTextureRect(sf::IntRect(0, 0, 55, 12));
//                            bullets[bullets.size() - 1].setTexture(texture_bullet);
//                            bullets[bullets.size() - 1].setScale(1, 1);
//                        }
//                        else{
//                            bullets.emplace_back(bullets.size(), -2*elapsed.asMilliseconds());
//                            bullets[bullets.size() - 1].setTextureRect(sf::IntRect(0, 0, 55, 12));
//                            bullets[bullets.size() - 1].setTexture(texture_bullet);
//                            bullets[bullets.size() - 1].setScale(-1, 1);
//                        }
//                        bullets[bullets.size() - 1].setPosition(hero_bounds.left + hero_bounds.width / 2, hero_bounds.top + hero_bounds.height / 2);
//                        clock2.restart();
//                    }
//                }



                hero.animate2(elapsed, walls, Piotrowi_zle_w_prawo, Piotrowi_zle_w_lewo);


                std::cout<<"         "<<hero_bounds.left<<"          "<<hero.get_actual_position()<<"          "<<elapsed.asMicroseconds()<<std::endl;


                // end the current frame
                window.display();
            }

// bohater porusza skacze i porusza się w kierunku poziomym tylko wtedy, gdy jest na podlożu

// if (event.type == sf::Event::KeyPressed){
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//        hero.toUp(elapsed);
//        }}
// if (event.type == sf::Event::KeyPressed){
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//        hero.toDown(elapsed);
//        }}
// if (event.type == sf::Event::KeyPressed){
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//        hero.toLeft(elapsed);
//        }}
// if (event.type == sf::Event::KeyPressed){
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//        hero.toRight(elapsed);
//        }
//        }

// animacja ruchu bohatera tylko wtedy, gdy jest na podlożu - w przeciwnym wypadku spadek



//        text.setString(to_string(score));    // aktualna liczba punktów do wyświetlen


    return 0;
}
