#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::CircleShape shape;
    sf::Texture texture;

    float speed;
    float normalSpeed;
    bool boosterActive;
    float boosterTimer;
    int lives;

public:
    Player(float x, float y, float radius);
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    float getX() const;
    float getY() const;
    float getRadius() const;
    void activateBooster();
    bool isBoosterActive() const;
    void loseLife();
    int getLives() const;
    void setPosition(float x, float y);
    void resetLives();
    void setRotation(float angle);



};
