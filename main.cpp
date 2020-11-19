#include "game.h"
#include <iostream>

int main(){
    bool replay = true;
    Game* game = NULL;
    while(replay){
        game = new Game();
        game->start();
        replay = game->gameOver();
        std::cout << "here play again? " << replay << std::endl;
        delete game;
    }
    
    return 0;
}