#include "Settings.h"
#include "AssetManager.cpp"
#include "Shape.h"
#include "Game.h"

auto Settings::showSettings(sf::Font& mainFont) -> void{
    auto bg = Shape(sf::Vector2f (window.getSize().x, window.getSize().y), sf::Color(0,0,0, 2), 0, 0);

    auto menu = Shape(sf::Vector2f (window.getSize().x / 2, window.getSize().y / 2), sf::Color::Black, 0,0, 10, sf::Color::Blue);
    menu.setPosition(window.getSize().x / 2 - menu.getSize().x / 2, window.getSize().y / 2 - menu.getSize().y / 2);

    auto buttonFont = Shape(sf::Vector2f(500, 50), sf::Color::Black, 0,0, 5, sf::Color::Blue);
    buttonFont.setPosition(menu.getPosition().x + menu.getSize().x/2 - buttonFont.getSize().x/2, menu.getPosition().y + menu.getSize().y/10);

    auto currentFontPlace = sf::Text("Current font: ", font,  30);
    currentFontPlace.setPosition(menu.getPosition().x + menu.getSize().x/2 - buttonFont.getSize().x/2 + 20, menu.getPosition().y + menu.getSize().y/10 + 5);

    auto currentFontText = sf::Text("", font,  30);
    currentFontText.setPosition(menu.getPosition().x + menu.getSize().x/2 - buttonFont.getSize().x/2 + 350, menu.getPosition().y + menu.getSize().y/10 + 5);

    auto buttonSize = Shape(sf::Vector2f(500, 50), sf::Color::Black, 0,0, 5, sf::Color::Blue);
    buttonSize.setPosition(buttonFont.getPosition().x, buttonFont.getPosition().y + buttonFont.getSize().y * 1.5f);

    auto currentSizePlace = sf::Text("Current size: ", font,  30);
    currentSizePlace.setPosition(menu.getPosition().x + menu.getSize().x/2 - buttonSize.getSize().x/2 + 20, menu.getPosition().y + menu.getSize().y/3 - 15);

    auto currentSizeText = sf::Text("", font,  30);
    currentSizeText.setPosition(menu.getPosition().x + menu.getSize().x/2 - buttonFont.getSize().x/2 + 350, menu.getPosition().y + menu.getSize().y/3 - 15);

    auto buttonSaves = Shape(sf::Vector2f(500,50), sf::Color::Black, 0,0,5,sf::Color::Blue);
    buttonSaves.setPosition(buttonSize.getPosition().x, buttonSize.getPosition().y + buttonSize.getSize().y * 1.5f);

    auto saves = sf::Text("Saves", font, 30);
    saves.setPosition(buttonSaves.getPosition().x + buttonSaves.getSize().x/2 - saves.getGlobalBounds().width/2,
                      buttonSaves.getPosition().y + buttonSaves.getSize().y/2 - saves.getGlobalBounds().height/2);

    auto buttonLeaderboards = Shape(sf::Vector2f(500,50), sf::Color::Black, 0,0,5,sf::Color::Blue);
    buttonLeaderboards.setPosition(buttonSaves.getPosition().x, buttonSaves.getPosition().y + buttonSaves.getSize().y * 1.5f);

    auto leaderboardsText = sf::Text("Leaderboards", font, 30);
    leaderboardsText.setPosition(buttonLeaderboards.getPosition().x + buttonLeaderboards.getSize().x/2 - leaderboardsText.getGlobalBounds().width/2,
                      buttonLeaderboards.getPosition().y + buttonLeaderboards.getSize().y/2 - leaderboardsText.getGlobalBounds().height/2);
///----------------------------------------------------------------------------------------------------------------------------------------
        while (window.isOpen()){
            auto event = sf::Event();
            auto mouse = sf::Mouse::getPosition(window);
            while (window.pollEvent(event)){
                if  (event.type == sf::Event::EventType::Closed) { window.close(); }
                else if (event.type == sf::Event::KeyPressed){if (event.key.code == sf::Keyboard::Key::Escape) return;}
                else if (event.type == sf::Event::MouseButtonPressed){
                    if (buttonFont.getGlobalBounds().contains(mouse.x, mouse.y)) changeFont(mainFont);
                    if (buttonSize.getGlobalBounds().contains(mouse.x, mouse.y)) {
                        changeSize();
                        Game::wave = std::pair<int, int>(0, 5);
                        Game::words = std::vector<std::vector<sf::Text>>();
                        Game::score = 0;
                        Game::wordsSpeed = 0;
                        Game::textEntered="";
                    }
                    if (buttonLeaderboards.getGlobalBounds().contains(mouse.x, mouse.y))leaderboards.showLeaders();
                    if (buttonSaves.getGlobalBounds().contains(mouse.x, mouse.y)) savings.showSavings();

                }
            }
            window.draw(bg);
            window.draw(menu);

            window.draw(buttonFont);
            window.draw(currentFontPlace);
            switch (currentFont) {
                case Arcade: currentFontText.setString("Arcade");        break;
                case Bruce:  currentFontText.setString("Bruce");         break;
                case KnightWarrior: currentFontText.setString("Knight"); break;
            }
            window.draw(currentFontText);

            window.draw(buttonSize);
            window.draw(currentSizePlace);
            switch (wordLength) {
                case Six:    currentSizeText.setString("Six");    break;
                case Nine:   currentSizeText.setString("Nine");   break;
                case Twelve: currentSizeText.setString("Twelve"); break;
            }
            window.draw(currentSizeText);

            window.draw(buttonSaves);
            window.draw(saves);

            window.draw(buttonLeaderboards);
            window.draw(leaderboardsText);

            window.display();
        }
///----------------------------------------------------------------------------------------------------------------------------------------
}

auto Settings::changeFont(sf::Font& mainFont) -> void{
   if ( currentFont == Arcade ) {
       mainFont = AssetManager::getFont("Ugly.ttf");
       currentFont = Bruce;
   }
   else if ( currentFont == Bruce ){
       mainFont = AssetManager::getFont("KnightWarrior.ttf");
       currentFont = KnightWarrior;
   }
   else if ( currentFont == KnightWarrior ) {
       mainFont = AssetManager::getFont("Arcade.ttf");
       currentFont = Arcade;
   }
}
auto Settings::changeSize() -> void{
    switch (wordLength) {
        case Six:    wordLength = Nine; break;
        case Nine:   wordLength = Twelve; break;
        case Twelve: wordLength = Six; break;
    }
}

