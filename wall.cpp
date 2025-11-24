#include "wall.hpp"

Wall::Wall() {
    shape.setSize(sf::Vector2f(0, 0));
    shape.setFillColor(sf::Color::Blue);
}

Wall::Wall(float x, float y, float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);
}

void Wall::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Wall::checkCollision(float playerX, float playerY, float playerRadius) {
    sf::FloatRect playerBounds(playerX - playerRadius, playerY - playerRadius,
                               playerRadius * 2, playerRadius * 2);
    return shape.getGlobalBounds().intersects(playerBounds);
}

sf::FloatRect Wall::getBounds() const {
    return shape.getGlobalBounds();
}