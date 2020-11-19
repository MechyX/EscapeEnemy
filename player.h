#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

typedef unsigned int uint;

class Player : public sf::Drawable, public sf::Transformable{
    //declare sprite
    sf::Texture texture;
    sf::VertexArray vertex;
    size_t xPos;
    size_t yPos;

    virtual void draw(sf::RenderTarget& target , sf::RenderStates states) const;

    public:
    Player();
    void moveDown(std::vector<std::pair<uint,uint> > obstacles);
    void moveUp(std::vector<std::pair<uint,uint> > obstacles);
    void moveLeft(std::vector<std::pair<uint,uint> > obstacles);
    void moveRight(std::vector<std::pair<uint,uint> > obstacles);
    std::pair<uint,uint> getPos();
};