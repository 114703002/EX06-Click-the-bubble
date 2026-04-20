#include "Bubble.h"
#include <cmath>
#include <cstdlib>

Bubble::Bubble(float x, float y, float radius) {
    shape.setPosition(x, y);
    shape.setRadius(radius);
    
    shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255)); 
    shape.setOrigin(radius, radius); 
    popped = false;
    points = 10; 
}


void Bubble::draw(sf::RenderWindow& window) const {
    if (!popped) {
        window.draw(shape);
    }
}

bool Bubble::checkClick(float mouseX, float mouseY) {
    if (popped) return false;

    float dx = shape.getPosition().x - mouseX;
    float dy = shape.getPosition().y - mouseY;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= shape.getRadius()) {
        popped = true;
        return true;
    }
    return false;
}

int Bubble::getPoints() const { return points; }
bool Bubble::isPopped() const { return popped; }