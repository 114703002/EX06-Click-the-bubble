#ifndef BUBBLE_H
#define BUBBLE_H

#include <SFML/Graphics.hpp>

class Bubble {
private:
    
    sf::CircleShape shape;
    bool popped;
    int points;

public:
    
    Bubble(float x, float y, float radius);

    void draw(sf::RenderWindow& window) const;

    bool checkClick(float mouseX, float mouseY);

    bool isPopped() const;
};

#endif // BUBBLE_H