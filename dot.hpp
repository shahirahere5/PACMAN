#pragma once
#include <SFML/Graphics.hpp>

class Dot {
private:
    sf::CircleShape shape;
    bool collected;

public:
    Dot(float x, float y);
    void draw(sf::RenderWindow& window);
    bool checkCollision(float playerX, float playerY, float radius);
    bool isCollected() const;
    void reset();
};
