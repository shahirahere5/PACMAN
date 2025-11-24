#include "player.hpp"
#include <exception>
#include <iostream>

Player::Player(float x, float y, float radius)
    : speed(150.f), normalSpeed(150.f), boosterActive(false), boosterTimer(0.f), lives(3) {
    
    if (!texture.loadFromFile("images/pacman.png")) {
        std::cerr << "Error loading pacman.png" << std::endl;
    }

    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setTexture(&texture);
    shape.setPosition(x, y);
}


void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed;
        shape.setRotation(90);  
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed;
        shape.setRotation(270);   
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed;
        shape.setRotation(0); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed;
        shape.setRotation(180);    
    }

    shape.move(movement * deltaTime);
}

void Player::setRotation(float angle) {
    shape.setRotation(angle);
}


void Player::update(float deltaTime) {
    if (boosterActive) {
        boosterTimer -= deltaTime;
        if (boosterTimer <= 0.f) {
            boosterActive = false;
            speed = normalSpeed;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Player::getX() const {
    return shape.getPosition().x;
}

float Player::getY() const {
    return shape.getPosition().y;
}

float Player::getRadius() const {
    return shape.getRadius();
}

void Player::activateBooster() {
    boosterActive = true;
    boosterTimer = 5.f;  
    speed = 300.f;       
}

bool Player::isBoosterActive() const {
    return boosterActive;
}

void Player::loseLife() {
    if (lives > 0) lives--;
}

int Player::getLives() const {
    return lives;
}

void Player::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

void Player::resetLives() {
    lives = 3;
}
