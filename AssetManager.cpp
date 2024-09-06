#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class AssetManager {
    inline static std::map<std::string, sf::Texture> textures = std::map<std::string, sf::Texture>();
    inline static std::map<std::string, sf::Font>    fonts    = std::map<std::string, sf::Font>();
public:
    static auto getTexture(const std::string fileName) -> sf::Texture&{
        {
            auto pairExists = textures.find(fileName);
            if (pairExists != textures.end()) {
                return pairExists->second;
            } else {
                auto &texture = textures[fileName];
                if (!texture.loadFromFile(fileName)){std::cerr << "Wrong texture name";}
                return texture;
            }
        }
    }

    static auto getFont(const std::string fileName) -> sf::Font& {
        {
            auto pairExists = fonts.find(fileName);
            if (pairExists != fonts.end()) {
                return pairExists->second;
            } else {
                auto &font = fonts[fileName];
                if (!font.loadFromFile(fileName)){std::cerr << "Wrong font name";}
                return font;
            }
        }
    }
};