#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.hpp"
#include "wall.hpp"
#include "dot.hpp"
#include "booster.hpp"
#include "ghost.hpp"
#include "map.hpp"
#include <SFML/Audio.hpp>

class Game {
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Wall> walls;
    
    std::vector<Booster> boosters;
    
    sf::Font font;
    sf::Text scoreText;
    sf::Text winText;
    int score;
    bool won;
    Map map;
    int lives;
    sf::Text livesText;
    sf::Text instructionText;
    bool gameOver = false;
    sf::Texture heartTexture;  
    std::vector<sf::Sprite> hearts;
    bool isPlayerRespawning;
    float deathCooldown;


public:
    Game();
    void run();
    void processEvents();
    void update(float deltaTime);
    void render();
    bool checkWallCollision(float x, float y);
    void restartGame();
};