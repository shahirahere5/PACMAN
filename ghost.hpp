#pragma once
#include <SFML/Graphics.hpp>
#include "wall.hpp"

class Ghost {
    private:
        sf::CircleShape shape;
        sf::Vector2f direction;
        float speed;
        float changeDirTimer;
        
    
    public:
        Ghost(float x, float y, float radius, sf::Color color);
        void update(float deltaTime, const std::vector<Wall>& walls);
        void draw(sf::RenderWindow& window);
        bool checkCollision(float x, float y, float radius);
        void setDirection(sf::Vector2f dir);
        sf::Vector2f getPosition() const;
        bool checkWallCollision(float x, float y, float radius, const std::vector<Wall>& walls);
    };