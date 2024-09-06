#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <filesystem>
#include "AssetManager.cpp"
#include "Shape.h"

class Savings {
    sf::RenderWindow& window;
    std::fstream file = std::fstream ("../saves.txt");
    sf::Font& font;
    static inline bool save1 = false;
    static inline bool save2 = false;
    static inline bool save3 = false;
public:
    Savings(sf::RenderWindow& window, std::string font) :
    window(window), font(AssetManager::getFont(font)) {
        if(!std::filesystem::exists("saves.txt"))
            auto create = std::ofstream ("saves.txt");
    }

    auto showSavings() -> void;
    auto saveResults(int score, int wave) -> void;
    auto takeData() -> std::vector<std::vector<int>>;
    auto updateValues(sf::Text& s1, sf::Text& s2, sf::Text& s3) -> void;
    };
