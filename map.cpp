#include "map.hpp"
#include <cmath>
#include "ghost.hpp"


Map::Map() : wallCount(0) {
    loadMap();    
}

void Map::loadMap() {
    
        wallCount = 0;
    
        
        walls[wallCount++] = Wall(20, 20, 720, 20);   // Top  //done
        walls[wallCount++] = Wall(20, 580, 720, 20);  // Bottom  //done
        walls[wallCount++] = Wall(20, 20, 20, 580);   // Left  //done
        walls[wallCount++] = Wall(730, 20, 20, 580);  // Right //done

        walls[wallCount++] = Wall(295, 80, 80, 20);
        walls[wallCount++] = Wall(480, 85, 80, 20);
        walls[wallCount++] = Wall(540, 85, 80, 20);
    
        
        walls[wallCount++] = Wall(85, 80, 20, 80);
        walls[wallCount++] = Wall(665, 80, 20, 80);
    
        
        walls[wallCount++] = Wall(280, 80, 20, 100);
        walls[wallCount++] = Wall(360, 80, 20, 100);
    
        
        walls[wallCount++] = Wall(220, 230, 100, 20);  // Top
        walls[wallCount++] = Wall(220, 240, 20, 140);  // Left
        walls[wallCount++] = Wall(220,380,300,20);
        walls[wallCount++] = Wall(500,230,20,150);
        walls[wallCount++] = Wall(400,230,120,20);
        walls[wallCount++] = Wall(380,230,20,80);
        walls[wallCount++] = Wall(380,300,50,20);
        walls[wallCount++] = Wall(85,160,80,20);
        walls[wallCount++] = Wall(150,160,20,180);
        walls[wallCount++] = Wall(40,340,130,20);
        walls[wallCount++] = Wall(40,250,40,20);
        walls[wallCount++] = Wall(190, 440, 20, 80);  
        walls[wallCount++] = Wall(200, 500, 120, 20);  
        walls[wallCount++] = Wall(300, 450, 70, 20);  
        walls[wallCount++] = Wall(380,160,100,20);
        walls[wallCount++] = Wall(480,100,20,80);
        walls[wallCount++] = Wall(580,150,105,20);
        walls[wallCount++] = Wall(580,150,20,290);
        walls[wallCount++] = Wall(580,300,80,20);
        walls[wallCount++] = Wall(670,220,80,20);
        walls[wallCount++] = Wall(670,380,80,20);
        walls[wallCount++] = Wall(500,500,160,20);
    
        
        walls[wallCount++] = Wall(90, 440, 100, 20);   // Left hor
        walls[wallCount++] = Wall(90, 460, 20, 120);    // Left vert
        walls[wallCount++] = Wall(580, 440, 100, 20);  // Right hor
        walls[wallCount++] = Wall(660, 460, 20, 60);   // Right vert
    
        
        walls[wallCount++] = Wall(300, 450, 20, 60);
        walls[wallCount++] = Wall(360, 450, 20, 70);
    
        
        walls[wallCount++] = Wall(260, 580, 80, 20);
        walls[wallCount++] = Wall(420, 580, 80, 20);

        
        boosters[0] = Booster(645.f, 480.f);     
        boosters[1] = Booster(55.f, 230.f);    
        boosters[2] = Booster(340.f, 490.f);    
    
    

   
    dots.clear();
    ghosts.clear();

    
    for (float y = 35; y <= 565; y += 35.f) {
        for (float x = 35; x <= 735; x += 30.f) {
    
            bool collidesWithWall = false;
            bool nearBooster = false;
            bool nearPlayer = true;
    
            
            for (int i = 0; i < wallCount; ++i) {
                sf::FloatRect wallBounds = walls[i].getBounds();
                sf::FloatRect dotBounds(x - 2, y - 2, 4, 4); 
    
                if (wallBounds.intersects(dotBounds)) {
                    collidesWithWall = true;
                    break;
                }
            }
    
            
            if ((std::abs(x - 645.f) < 16.f && std::abs(y - 480.f) < 16.f) ||    
                (std::abs(x - 55.f)  < 16.f && std::abs(y - 230.f) < 16.f) ||    
                (std::abs(x - 340.f) < 16.f && std::abs(y - 490.f) < 16.f)) {    
                nearBooster = true;
            }    
            
            if (!collidesWithWall && !nearBooster ) {
                dots.emplace_back(x, y);
            }
        }
    }


ghosts.emplace_back(400.f, 300.f, 15.f, sf::Color::Red);
ghosts.emplace_back(300.f, 400.f, 15.f, sf::Color::Red);
ghosts.emplace_back(500.f,200.f,15.f,sf::Color::Red);
ghosts.emplace_back(100.f,400.f,15.f,sf::Color::Red);


}


void Map::render(sf::RenderWindow& window) {
    for (int i = 0; i < wallCount; ++i) {
        walls[i].draw(window);
    }

    for (auto& booster : boosters) {
        booster.draw(window);
    }
}

bool Map::checkCollision(float playerX, float playerY, float playerRadius) {
    for (int i = 0; i < wallCount; ++i) {
        if (walls[i].checkCollision(playerX, playerY, playerRadius)) {
            return true;
        }
    }
    return false;
}

bool Map::activateBooster(float playerX, float playerY) {
    for (auto& booster : boosters) {
        if (booster.checkCollision(playerX, playerY, 16.f)) {
            booster.activate();
            return true;
        }
    }
    return false;
}

void Map::updateGhosts(float deltaTime, const std::vector<Wall>& walls)
{
    for (auto& ghost : ghosts)
    {
        ghost.update(deltaTime, walls); 
    }
}

void Map::resetDots() {
    for (auto& dot : dots) {  
        dot.reset();  
    }
}

void Map::resetBoosters() {
    for (auto& booster : boosters) {
        booster.reset();  
    }
}


