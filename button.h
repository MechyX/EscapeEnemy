#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class Button{
    //basically a quad
    sf::RectangleShape graphicButton;
    sf::Vector2f textPos;
    sf::Text graphicText;
    sf::Font textFont;

    public:
    Button();
    Button(std::string text, sf::Vector2f pos , sf::Vector2f size , sf::Font font);
    sf::RectangleShape& returnButton();
    void setBackgroundColor(sf::Color buttonColor);
    void setTextColor(sf::Color textColor);
    void drawButton(sf::RenderWindow& window);

    //check if the button is clicked or not
    bool isClicked(sf::Vector2f point);
};