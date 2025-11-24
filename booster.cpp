#include "booster.hpp"
#include <cmath>

Booster::Booster() {
    
    shape.setRadius(10);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(0, 0); 

}

Booster::Booster(float x, float y) : active(true) {

    shape.setRadius(8.f);
    shape.setOrigin(8.f, 8.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);

}

void Booster::draw(sf::RenderWindow& window) {
    if (active)
        window.draw(shape);

}

bool Booster::checkCollision(float playerX, float playerY, float radius) {

    if (!active) return false;

    float dx = shape.getPosition().x - playerX;
    float dy = shape.getPosition().y - playerY;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < (radius + shape.getRadius())) {
        activate();  
        return true;
    }

    return false;

}

bool Booster::isActive() const {
    return active;

}

void Booster::activate() {
    active = false; 

}

void Booster::reset(){
    active = true;

}
