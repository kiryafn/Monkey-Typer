#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.cpp"
#include "Leaderboards.h"
#include "Savings.h"

class Settings {
    sf::RenderWindow& window;
    Leaderboards& leaderboards;
    Savings& savings;
    sf::Font font;
public:
    enum Font {KnightWarrior, Arcade, Bruce};
    enum Size {Six, Nine, Twelve};
public:
    static inline Size wordLength = Six;
    static inline Font currentFont = Arcade;
    Settings(sf::RenderWindow &window1, std::string font1, Leaderboards &leaderboards1, Savings& savings1) :
            window(window1), font(AssetManager::getFont(font1)), leaderboards(leaderboards1), savings(savings1) {}

    auto showSettings(sf::Font& mainFont) -> void;
    auto changeFont(sf::Font& mainFont) -> void;
    auto changeSize() -> void;
};

