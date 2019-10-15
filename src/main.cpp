#include <SFML/Graphics.hpp>
#include <time.h>

#include "InputHandler.h"
#include "Map.h"
#include "Enemy.h"
#include "Mushroom.h"
using namespace sf;

const int map_y = 50;
const int map_x = 100;

int main() {
    Map* map = new Map(map_x, map_y);
    InputHandler handler;
    Enemy* enemy1 = Enemy::createEnemy(map_x / 4 * 1, map_y / 4 * 1, false);
    Enemy* enemy2 = Enemy::createEnemy(map_x / 4 * 3, map_y / 4 * 3, false);
    Enemy* enemy3 = Enemy::createEnemy(map_x / 4 * 1, map_y / 4 * 3, false);
    Enemy* enemy4 = Enemy::createEnemy(map_x / 4 * 3, map_y / 4 * 1, false);
    Enemy* enemy5 = Enemy::createEnemy(map_x / 4 * 2, map_y / 4 * 2, true);
    Mushroom* mushroom = Mushroom::createMushroom(BLUE_MUSHROOM);

    map->enemy.push_back(enemy1);
    map->enemy.push_back(enemy2);
    map->enemy.push_back(enemy3);
    map->enemy.push_back(enemy4);
    map->enemy.push_back(enemy5);
    map->mushroom.push_back(mushroom);

    srand(time(0));
    std::pair<size_t, size_t> size =  map->getMapSize();
    RenderWindow window(VideoMode(size.first, size.second), "");
    window.setFramerateLimit(60);


    bool Game=true;
    float timer=0, delay=0.04; 
    Clock clock;

    Texture t;
    t.loadFromFile("../images/gameover.png");
    Sprite game_over(t);
    game_over.setPosition(650, 350);
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Escape) {
                    Game = true;
                    delete map;
                    map = new Map(map_x, map_y);
                    InputHandler handler;
                    enemy1 = Enemy::createEnemy(map_x / 4 * 1, map_y / 4 * 1, false);
                    enemy2 = Enemy::createEnemy(map_x / 4 * 3, map_y / 4 * 3, false);
                    enemy3 = Enemy::createEnemy(map_x / 4 * 1, map_y / 4 * 3, false);
                    enemy4 = Enemy::createEnemy(map_x / 4 * 3, map_y / 4 * 1, false);
                    enemy5 = Enemy::createEnemy(map_x / 4 * 2, map_y / 4 * 2, true);
                    mushroom = Mushroom::createMushroom(BLUE_MUSHROOM);

                    map->enemy.push_back(enemy1);
                    map->enemy.push_back(enemy2);
                    map->enemy.push_back(enemy3);
                    map->enemy.push_back(enemy4);
                    map->enemy.push_back(enemy5);
                    map->mushroom.push_back(mushroom);
                }
        }

        if (timer > delay) {
            if (!Game) {
                timer = 0;
                window.clear();
                window.draw(game_over);
                window.display();
            } else {
                handler.handleInput(mushroom);
                Game = map->updateMap();
                timer = 0;
                window.clear();
                map->drawMap(&window);
                window.display();
            }
        }
    }
    return 0;
}
