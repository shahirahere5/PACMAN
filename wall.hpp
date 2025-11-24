#pragma once
#include <SFML/Graphics.hpp>

class Wall {
private:
    sf::RectangleShape shape;

public:
    Wall();
    Wall(float x, float y, float width, float height);
    
    void draw(sf::RenderWindow& window);
    bool checkCollision(float playerX, float playerY, float playerRadius);
    sf::FloatRect getBounds() const;
};