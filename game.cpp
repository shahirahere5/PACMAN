#include "game.hpp"
#include <iostream>

sf::SoundBuffer dotBuffer;
sf::Sound dotSound;

sf::SoundBuffer boosterBuffer;
sf::Sound boosterSound;

sf::SoundBuffer deathBuffer;
sf::Sound deathSound;

sf::SoundBuffer backgroundBuffer;
sf::Sound backgroundSound;

Game::Game()
    : window(sf::VideoMode(800, 650), "Pac-Man"), player(710.f, 555.f, 15.f), score(0), won(false), gameOver(false),isPlayerRespawning(false),deathCooldown(0.f){

    font.loadFromFile("arial.ttf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(10, 610);
    scoreText.setFillColor(sf::Color::White);

    winText.setFont(font);
    winText.setCharacterSize(30);
    winText.setPosition(250, 300);
    winText.setFillColor(sf::Color::Green);
    winText.setString("You Win!");

    lives = 3;
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(690, 610);
    livesText.setString("Lives: " + std::to_string(lives));

    instructionText.setFont(font);
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(240, 350);
    instructionText.setString("Press R to Restart or ESC to Exit");

    if (!dotBuffer.loadFromFile("sounds/pickup.wav")) {}
    dotSound.setBuffer(dotBuffer);

    if (!boosterBuffer.loadFromFile("sounds/booster.wav")) {}
    boosterSound.setBuffer(boosterBuffer);

    if (!deathBuffer.loadFromFile("sounds/death.wav")) {
    std::cerr << "Failed to load death.wav\n";
    }

    if(!backgroundBuffer.loadFromFile("sounds/background.wav")){}
    backgroundSound.setBuffer(backgroundBuffer);

    deathSound.setBuffer(deathBuffer);
    deathSound.setVolume(100);  
    backgroundSound.setVolume(80);
    dotSound.setVolume(85);
    backgroundSound.setLoop(true);  
    backgroundSound.play(); 

    if (!heartTexture.loadFromFile("images/heart.png")) {
        std::cerr << "Error loading heart image!" << std::endl;
    }
}


void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        if (!won && !gameOver)
            update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                restartGame();
            }
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void Game::update(float deltaTime) {
    player.handleInput(deltaTime);

    if (checkWallCollision(player.getX(), player.getY())) {
        player.handleInput(-deltaTime);
    }

    if (isPlayerRespawning) {
        deathCooldown -= deltaTime;
        if (deathCooldown <= 0.f) {
            player.setPosition(710.f, 555.f); 
            isPlayerRespawning = false;
        }
        return;
    }



    player.update(deltaTime);

    if (map.activateBooster(player.getX(), player.getY())) {
        boosterSound.play();
        player.activateBooster();
    }

    for (auto& dot : map.getDots()) {
        if (dot.checkCollision(player.getX(), player.getY(), player.getRadius())) {
            dotSound.play();
            score++;
        }
    }

    map.updateGhosts(deltaTime, walls);
    for (auto& ghost : map.getGhosts()) {
        

        if (ghost.checkCollision(player.getX(), player.getY(), player.getRadius())) {
        if (!player.isBoosterActive() && !isPlayerRespawning) {
            lives--;
            deathSound.play();
            isPlayerRespawning = true;
            deathCooldown = 2.f;
        }

        }


        if (lives <= 0) {
            gameOver = true;
            return;
        }
    }

    won = true;
    for (const auto& dot : map.getDots()) {
        if (!dot.isCollected()) {
            won = false;
            break;
        }
    }

    scoreText.setString("Score: " + std::to_string(score));
}

void Game::render() {
    window.clear();

    map.render(window);
    for (auto& wall : walls) wall.draw(window);
    for (auto& dot : map.getDots()) dot.draw(window);
    for (auto& ghost : map.getGhosts()) ghost.draw(window);

    if (!isPlayerRespawning || static_cast<int>(deathCooldown * 5) % 2 == 0) {
    player.draw(window);
}

    window.draw(scoreText);

    hearts.clear();  
    for (int i = 0; i < lives; ++i) {
        sf::Sprite heart(heartTexture);
        heart.setPosition(700.f - i * 30.f, 590.f);  
        
        float scaleX = 60.f / heart.getLocalBounds().width;
        float scaleY = 60.f / heart.getLocalBounds().height;
        heart.setScale(scaleX, scaleY);
        hearts.push_back(heart);
    }

    for (auto& heart : hearts) {
        window.draw(heart);
    }

    if (won || gameOver) {
        sf::RectangleShape background(sf::Vector2f(400.f, 100.f)); 
        background.setFillColor(sf::Color::Black);
        background.setPosition(180.f, 290.f); 

        window.draw(background); 

        if (won) {
            window.draw(winText);
        } else if (gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(40);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("Game Over!");
            gameOverText.setPosition(250, 300);

            window.draw(gameOverText);
        }

        window.draw(instructionText); 
    }

    window.display();
}

bool Game::checkWallCollision(float x, float y) {
    return map.checkCollision(x, y, player.getRadius());
}

void Game::restartGame() {
    player.setPosition(710.f, 555.f);
    player.resetLives();  
    score = 0;
    lives = 3;
    won = false;
    gameOver = false;
    map.resetDots();
    map.resetBoosters();
}

