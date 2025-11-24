#include "dot.hpp"
#include <cmath>

Dot::Dot(float x, float y) : collected(false) {
    shape.setRadius(6.f);
    shape.setOrigin(4.f, 4.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
}

void Dot::draw(sf::RenderWindow& window) {
    if (!collected)
        window.draw(shape);
}

bool Dot::checkCollision(float playerX, float playerY, float radius) {
    if (collected) return false;

    float dx = shape.getPosition().x - playerX;
    float dy = shape.getPosition().y - playerY;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < radius + shape.getRadius()) {
        collected = true;
        return true;
    }
    return false;
}

bool Dot::isCollected() const {
    return collected;
}

void Dot::reset() {
    collected = false;  
}
