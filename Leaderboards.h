#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <filesystem>
#include "AssetManager.cpp"
#include "Shape.h"

class Leaderboards {
    sf::RenderWindow& window;
    std::fstream file = std::fstream ("leaderboard.txt");
    sf::Font& font;

public:
    Leaderboards(sf::RenderWindow& window, std::string font) :
    window(window), font(AssetManager::getFont(font)) {}

    auto sortByScore() -> void;
    auto showLeaders() -> void;
    auto saveResults(std::string name, int score) -> void;
    auto updateValues(Shape &menu, sf::Text &nameText, sf::Text &scoreText) -> void;
};
