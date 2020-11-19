#include "enemy.h"

Enemy :: Enemy(){
     vertex.setPrimitiveType(sf::Quads);
     vertex.resize(4);
     if(!texture.loadFromFile("enemyasset.png")){
          std::cout << "Error loading enemy texture " <<std::endl;
          exit(1);
     }

    std::cout << "Loaded Enemy Texture" << std::endl;

     //load from file the enemy and set its position away from the player also check path finding before
    vertex[0].position = sf::Vector2f(0.f,0.f);
    vertex[1].position = sf::Vector2f(96.f,0.f);
    vertex[2].position = sf::Vector2f(96.f,128.f);
    vertex[3].position = sf::Vector2f(0.f,128.f);

    vertex[0].texCoords = sf::Vector2f(0.f,0.f);
    vertex[1].texCoords = sf::Vector2f(96.f,0.f);
    vertex[2].texCoords = sf::Vector2f(96.f,128.f);
    vertex[3].texCoords = sf::Vector2f(0.f,128.f);

    this->setPosition(28.f,440.f);
    xPos = 13;
    yPos = 0;
    this->setScale(0.3f,0.3f);
}

void Enemy :: findPath(std::pair<uint,uint> playerPos){
    
    //pop all coords from stack
    while(!path.empty())
       path.pop();

    //map for path finding
    int grid[14][14] = { 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1}, 
        { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 ,1 ,1 ,1 ,1},  
        { 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 ,1 ,1 ,1 ,1}, 
        { 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 ,1 ,1 ,1 ,1}, 
        { 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 ,1 ,1 ,1 ,1}, 
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,0 ,1}, 
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,0 ,1}, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1},  
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1}, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1}, 
        { 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1}, 
        { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 ,0 ,1 ,1 ,1}, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1}, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1}
    };

    if(!aStarSearch(grid, getPos() ,playerPos , path))
        std::cout << "Cannot find path" << std::endl;

}


void Enemy :: draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &texture;

    target.draw(vertex, states);
}

std::pair<uint,uint> Enemy :: getPos(){
     return std::make_pair(xPos,yPos);
}

void Enemy :: moveNext(){
    if(path.empty())    
        return;

    std::pair<uint,uint> nextNode = path.top();
    path.pop();

    uint x = nextNode.first;
    uint y = nextNode.second;


    if(y == yPos  && x == xPos + 1)
        moveDown();
    
    else if(y == yPos && x == xPos - 1)
        moveUp();
    
    else if(y == yPos - 1 && x == xPos)
        moveLeft();
    
    else if(y == yPos + 1 && x == xPos)
        moveRight();
}

void Enemy :: moveDown(){
     if(!(xPos + 1 > 13)){
        move(0.f,32.f);
        xPos = xPos + 1;
    }
}

void Enemy :: moveUp(){
     if(!(xPos - 1 <  0)){
       move(0.f,-32.f);
       xPos = xPos - 1;
   }
}

void Enemy :: moveLeft(){
    if(!(yPos - 1 < 0)){
        move(-32.f,0.f);
        yPos = yPos - 1;
    }
}

void Enemy :: moveRight(){
    if(!(yPos + 1 > 13)){
        move(32.f,0.f);
        yPos = yPos + 1;
    }  
}