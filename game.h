#include <SFML\Graphics.hpp>
#include "map.h"
#include "enemy.h"
#include "player.h"
#include "button.h"
#include <iostream>
#include <utility>


typedef unsigned int uint;

class Game{
    //create and set window size
     sf::RenderWindow* window;
     //have a map(i.e grid)
     Map* gameMap;
     Player* player;
     Enemy* enemy;
     
    public:
    //default constructor
        sf::Time gameTime;
        Game();
        ~Game();
        void showMenu();
        void start();
        void replay();
        void quit();
        bool gameOver();
};