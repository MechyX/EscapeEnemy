#include "button.h"

Button :: Button(std::string text, sf::Vector2f pos , sf::Vector2f size ,  sf::Font font){
    textFont = font;

    graphicText.setFont(textFont);
    graphicText.setString(text);
    graphicText.setCharacterSize(50);
    graphicText.setStyle(sf::Text::Bold);

    graphicButton.setPosition(pos);
    graphicButton.setSize(size);

    float xPos = (pos.x + size.x / 2) - (graphicText.getLocalBounds().width / 2);
    float yPos = (pos.y + size.y / 2) - (graphicText.getLocalBounds().height / 2);
    graphicText.setPosition(xPos, yPos);
}

sf::RectangleShape& Button :: returnButton(){
    return graphicButton;
}

bool Button :: isClicked(sf::Vector2f point){
    return graphicButton.getGlobalBounds().contains(point);
}

void Button :: setBackgroundColor(sf::Color buttonColor){
    graphicButton.setFillColor(buttonColor);
}

void Button :: drawButton(sf::RenderWindow& window){
    window.draw(graphicButton);
    window.draw(graphicText);
}

void Button :: setTextColor(sf::Color textColor){
    graphicText.setFillColor(textColor);
}