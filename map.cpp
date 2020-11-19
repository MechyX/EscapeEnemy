#include "map.h"

Map :: Map(){
    
}

void Map :: draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = &texture;

    target.draw(vertexMap, states);
}

bool Map :: intialize(int *mapArray , sf::Vector2u tileSize , uint width, uint height){
     
     if (!texture.loadFromFile("tilemap.png")){
        std::cout << "Error! cannot load map texture" << std::endl;
        return false;
    }

    std::cout << "Loaded Map texture" << std::endl; 

    vertexMap.resize(width*height*4);
    vertexMap.setPrimitiveType(sf::Quads);


    for(uint i = 0 ; i < width ; i++){
        for(uint j = 0 ; j <height; ++j){

            int tileNumber = mapArray[i + j * width];

            int tu = tileNumber % (texture.getSize().x / tileSize.x);
            int tv = tileNumber / (texture.getSize().x / tileSize.x);

            sf::Vertex* tile = &vertexMap[(i + j * width) * 4];
        
            tile[0].position = sf::Vector2f(i*tileSize.x , j * tileSize.y);
            tile[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            tile[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            tile[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            tile[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            tile[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            tile[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            tile[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}