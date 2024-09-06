#pragma once
#include <SFML/Graphics.hpp>

class Shape : public sf::RectangleShape{
public:
    Shape(sf::Vector2f size, sf::Color color, int posX, int posY, int outlineThickness = 0, sf::Color outline = sf::Color::Black) : sf::RectangleShape(size) {
        this->setFillColor(color);
        this->setPosition(posX, posY);
        this->setOutlineThickness(outlineThickness);
        this->setOutlineColor(outline);
    }
};