#include "player.h"


Player :: Player(){
    vertex.setPrimitiveType(sf::Quads);
    vertex.resize(4);
    
    //load from enemy texture
    if(!texture.loadFromFile("playerasset.png")){
        std::cout << "Error! cannot load player texture" << std::endl;
        exit(1);
    }

    std::cout << "Loaded Player Texture" << std::endl; 

    vertex[0].position = sf::Vector2f(0.f,0.f);
    vertex[1].position = sf::Vector2f(96.f,0.f);
    vertex[2].position = sf::Vector2f(96.f,128.f);
    vertex[3].position = sf::Vector2f(0.f,128.f);

    vertex[0].texCoords = sf::Vector2f(0.f,0.f);
    vertex[1].texCoords = sf::Vector2f(96.f,0.f);
    vertex[2].texCoords = sf::Vector2f(96.f,128.f);
    vertex[3].texCoords = sf::Vector2f(0.f,128.f);
    
    this->setPosition(28.f,24.f);
    xPos = 0;
    yPos = 0;
    this->setScale(0.3f,0.3f);
}

void Player :: draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &texture;

    target.draw(vertex, states);
}

//pass in the map array to detect obstacles

void Player :: moveDown(std::vector<std::pair<uint,uint> > obstacles){
    
    //check for obstacles
    for(size_t i = 0 ; i < obstacles.size(); i++){
        if(std::make_pair(xPos + 1 , yPos) == obstacles.at(i))
            return;
    }

    if(!(xPos + 1 > 13)){
        move(0.f,32.f);
        xPos = xPos + 1;
    }
}

void Player :: moveUp(std::vector<std::pair<uint,uint> > obstacles){

    for(size_t i = 0 ; i < obstacles.size(); i++){
        if(std::make_pair(xPos - 1 , yPos) == obstacles.at(i))
            return;
    }

   if(!(xPos - 1 + 1 <  1)){
       move(0.f,-32.f);
       xPos = xPos - 1;
   }
}

std::pair<uint,uint> Player :: getPos(){
    return std::make_pair(xPos,yPos);
}


void Player :: moveLeft(std::vector<std::pair<uint,uint> > obstacles){

    for(size_t i = 0 ; i < obstacles.size(); i++){
        if(std::make_pair(xPos , yPos - 1) == obstacles.at(i))
            return;
    }

    if(!(yPos + 1 - 1 < 1)){
        move(-32.f,0.f);
        yPos = yPos - 1;
    }  
}

void Player :: moveRight(std::vector<std::pair<uint,uint> > obstacles){

    for(size_t i = 0 ; i < obstacles.size(); i++){
        if(std::make_pair(xPos , yPos + 1) == obstacles.at(i))
            return;
    }


    if(!(yPos + 1 > 13)){
        move(32.f,0.f);
        yPos = yPos + 1;
    }  
}