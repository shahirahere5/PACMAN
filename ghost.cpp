#include "ghost.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "wall.hpp"

Ghost::Ghost(float x, float y, float radius, sf::Color color): speed(100.f), direction(1.f, 0.f), changeDirTimer(0.f) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(color);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Ghost::update(float deltaTime, const std::vector<Wall>& walls)
{
    
    changeDirTimer += deltaTime;
    if (changeDirTimer >= 5.0f)
    {
        int dir = std::rand() % 4;
        switch (dir)
        {
        case 0:
            direction = {1.f, 0.f};  
            break;
        case 1:
            direction = {-1.f, 0.f}; 
            break;
        case 2:
            direction = {0.f, 1.f};  
            break;
        case 3:
            direction = {0.f, -1.f}; 
            break;
        }
        changeDirTimer = 0.f;
    }

    sf::Vector2f nextPos = shape.getPosition() + direction * speed * deltaTime;

    sf::CircleShape temp = shape;
    temp.setPosition(nextPos);

    for (size_t i = 0; i < walls.size(); ++i)
    {
        
        if (temp.getGlobalBounds().intersects(walls[i].getBounds()))
        {
            
            direction.x *= -1;
            direction.y *= -1;
            return; 
        }
    }

    
    if (nextPos.x - shape.getRadius() < 0 || nextPos.x + shape.getRadius() > 800)
    {
        direction.x *= -1;
    }
    if (nextPos.y - shape.getRadius() < 0 || nextPos.y + shape.getRadius() > 600)
    {
        direction.y *= -1;
    }

   
    shape.setPosition(nextPos);
}




void Ghost::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

bool Ghost::checkCollision(float x, float y, float radius) {
    float dx = x - shape.getPosition().x;
    float dy = y - shape.getPosition().y;
    float dist = std::sqrt(dx * dx + dy * dy);

    return dist < radius + shape.getRadius();
}

void Ghost::setDirection(sf::Vector2f dir) {
    direction = dir;
}

sf::Vector2f Ghost::getPosition() const {
    return shape.getPosition();
}
