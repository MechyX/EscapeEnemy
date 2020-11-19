#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <set>
#include <stack>
#include "utils.h"

#define COL 14
typedef unsigned int uint;


class Enemy: public sf::Drawable,public sf::Transformable{
    //Declare sprite
    sf::VertexArray vertex;
    sf::Texture texture;
    size_t xPos;
    size_t yPos;
    std::stack<Pair> path;
    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();

    virtual void draw(sf::RenderTarget& target , sf::RenderStates states) const;

    public:
    Enemy();
    void moveNext();
    void findPath(std::pair<uint,uint> playerPos);
    std::pair<uint,uint> getPos();
    //also include logic for the thing
};