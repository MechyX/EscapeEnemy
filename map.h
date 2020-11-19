#include<SFML/Graphics.hpp>
#include <iostream>

typedef unsigned int uint;


class Map: public sf::Drawable , public sf::Transformable{

    sf::VertexArray vertexMap;
    sf::Texture texture;
    virtual void draw(sf::RenderTarget& target , sf::RenderStates states) const;
    
    
    public:  
    //create and render map
        Map();
        bool intialize(int* mapArray , sf::Vector2u tileSize , uint width, uint height);
};