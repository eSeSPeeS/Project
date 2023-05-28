#ifndef THINGS_H
#define THINGS_H

#include <string>

#include <SFML/Graphics.hpp>

class Things : public sf::Sprite{
private:
    sf::Vector2f position;
    //    sf::Vector2f size;
public:
    Things(int things_number, sf::Vector2f pozycja){
            position=pozycja;
            setPosition(position);
        }
    sf::FloatRect polozenie();
};

#endif // THINGS_H
