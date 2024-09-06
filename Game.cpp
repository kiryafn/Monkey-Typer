#include "Game.h"
#include "Shape.h"
#include <ctime>
#include <SFML/Audio.hpp>
auto Game::showGame() -> void{
    srand(time(nullptr));

    auto pop = sf::Music();
    pop.openFromFile("pop.wav");

    auto yellowLine = Shape(sf::Vector2f(2, window.getSize().y), sf::Color::Yellow, window.getSize().x - 500, 0);

    auto redLine = Shape(sf::Vector2f(2, window.getSize().y), sf::Color::Red, window.getSize().x - 200, 0);

    auto deadLine = Shape(sf::Vector2f(2, window.getSize().y), sf::Color::Red, window.getSize().x, 0);

    auto typeArea = Shape(sf::Vector2f(window.getSize().x, 200), sf::Color::Black, 0, window.getSize().y - 200, 10, sf::Color::Cyan);

    auto scoreText = sf::Text("Score", font, 48);
    scoreText.setPosition(20, window.getSize().y - 160);

    auto waveText = sf::Text("Wave", font, 48);
    waveText.setPosition(window.getSize().x - 20 - waveText.getGlobalBounds().width, window.getSize().y - 160);

    auto userScore = sf::Text(std::to_string(score), font, 48);
    userScore.setPosition(70, window.getSize().y - 100);

    auto waveTextInt = sf::Text("", font, 48);
    waveTextInt.setPosition(window.getSize().x - 70 - waveTextInt.getGlobalBounds().width, window.getSize().y - 100);

///-------------------------------------------------------------------------------------------------------

    while (window.isOpen()){


        if (words.empty()) {
            if (score == 0) userScore.setString(std::to_string(score));
            //std::cout << wave.first;
            wave.first++;
            wave.second += 5;
            addNewWords(typeArea);
        }
        wordsSpeed = 0.01 * wave.first;

        auto event = sf::Event();
        while (window.pollEvent(event)){
            if  (event.type == sf::Event::EventType::Closed) { window.close(); }
            else if (event.type == sf::Event::TextEntered){
                if (event.text.unicode < 128){
                    if (event.text.unicode == '\b') {
                        if (!textEntered.empty()) textEntered.pop_back();
                    }
                    else textEntered += static_cast<char>(event.text.unicode);
                }
            }
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Key::Escape){
                    settings.showSettings(font);
                }else shortcuts(event);
            }
        }
        window.clear();
        Game::updateFrame(words, yellowLine, redLine, deadLine, userScore,
                           typeArea, scoreText, waveText, waveTextInt, pop);
        window.display();
    }
}

///----------------------------------------------------------------------------------------------------------------------------------------

auto Game::getWordLength() -> std::vector<std::string>&{
    if (Settings::wordLength == Settings::Size::Six) return sixLength;
    else if (Settings::wordLength == Settings::Size::Nine) return nineLength;
    else return twelveLength;
}

auto Game::addNewWords(Shape& shape) -> void{
    auto x = 0;
    auto globalX = 0;
    for (int i = 0; i < wave.second; ++i) {
        auto randomI = int(rand() % 100);
        auto randomY = int(rand() % ((int)shape.getPosition().y - 100));
        auto tempWord = getWordLength()[randomI];
        auto charVector = std::vector<sf::Text>();  ///word

        for (int j = 0; j < tempWord.size(); ++j) {
            auto letter = sf::Text(tempWord[j], font, 35);
            letter.setPosition(x, 0);
            unsigned int spacing = font.getKerning(tempWord[j],tempWord[j+1],35);
            x += letter.getLocalBounds().width + spacing + 5;

            charVector.push_back(letter);
        }

        auto vectorMove = [globalX, randomY](std::vector<sf::Text>& text) -> void{
            for (int j = 0; j < text.size(); ++j) {
                 text[j].move(globalX, randomY);
            }
        };

        auto vectorMoveIfCollides = [](std::vector<sf::Text>& text) -> void{
            for (int j = 0; j < text.size(); ++j) {
                text[j].move(0, 100);
            }
        };

        vectorMove(charVector);
        words.push_back(charVector);

        auto checkIfCollides = [vectorMoveIfCollides](std::vector<sf::Text>& text1, std::vector<sf::Text>& text2) -> void{
                for (int j = 0; j < text2.size(); ++j) {
                    if (text1[text1.size()-1].getGlobalBounds().intersects(text2[j].getGlobalBounds())){
                        vectorMoveIfCollides(text1);
                        return;
                    }
            }
        };

        //WORDS CANT INTERSECT
        if (words.size() >=2){
            checkIfCollides(words[words.size()-1], words[words.size()-2]);
        }
        charVector = std::vector<sf::Text>();

        switch (Settings::wordLength) {
            case Settings::Six: globalX    -= 230; break;
            case Settings::Nine: globalX   -= 300; break;
            case Settings::Twelve: globalX -= 400; break;
        }
    }
}

auto Game::updateFrame(std::vector<std::vector<sf::Text>>& words, sf::RectangleShape const& yellow,
                       sf::RectangleShape const& red, sf::RectangleShape const& dead, sf::Text& userScore,
                       Shape& typeArea, sf::Text& scoreText, sf::Text& waveText, sf::Text& waveTextInt, sf::Music& pop) -> void{
    
    auto yourText = sf::Text(textEntered, font, 50);
    yourText.setPosition(window.getSize().x / 2, window.getSize().y - 150);

    waveTextInt.setString(std::to_string(wave.first));
    userScore.setString(std::to_string(score));

    window.draw(yellow);
    window.draw(red);
    window.draw(typeArea);
    window.draw(scoreText);
    window.draw(waveText);
    window.draw(waveTextInt);
    
    auto getWordFromChars = [](std::vector<sf::Text>& text)-> std::string {
        auto toReturn = std::string("");
        for (auto& x : text) toReturn += x.getString();
        return toReturn;
    };

    for (int i = 0; i < words.size(); i++){
        auto currentPart = std::string("");
        for (int j = 0; j < words[i].size(); ++j) {

            currentPart += words[i][j].getString();
            if (textEntered == currentPart) {
                words[i][j].setFillColor(sf::Color::Cyan);
            }
            else if (textEntered == ""){
                if(words[i][j] .getPosition().x < yellow.getPosition().x) words[i][j].setFillColor(sf::Color::White);
                else if(words[i][j] .getPosition().x > yellow.getPosition().x && words[i][j] .getPosition().x < red.getPosition().x) words[i][j].setFillColor(sf::Color::Yellow);
                else words[i][j].setFillColor(sf::Color::Red);
            }

            if (words[i][j].getFillColor() != sf::Color::Cyan){
                if (words[i][j].getGlobalBounds().intersects(yellow.getGlobalBounds()))  words[i][j].setFillColor(sf::Color::Yellow);
                else if (words[i][j].getGlobalBounds().intersects(red.getGlobalBounds())) words[i][j].setFillColor(sf::Color::Red);
            }

            if (textEntered == getWordFromChars(words[i])){
                words.erase(words.begin() + i);
                score++;
                pop.play();
                textEntered = "";
            }
            window.draw(words[i][j]);
            words[i][j].move(wordsSpeed, 0);

            if (words[i][j].getGlobalBounds().intersects(dead.getGlobalBounds())) end = true;
            if (end){
                end = !end;
                endGameMenu();
                settings.showSettings(font);
                restart();
                return;
            }
        }
        currentPart = "";
    }
    yourText.setPosition(sf::Vector2f(
            window.getSize().x / 2 - yourText.getGlobalBounds().width / 2,
            window.getSize().y - typeArea.getGlobalBounds().height / 2
    ));
    window.draw(yourText);
    window.draw(userScore);
}

auto Game::shortcuts(sf::Event event) -> void{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) textEntered = "";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::S)) savings.saveResults(score,wave.first);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
        restart();
    }
}
auto Game::endGameMenu() -> void {
    auto menu = Shape(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Color::Black, 0, 0, 10,sf::Color::Magenta);
    menu.setPosition(window.getSize().x / 2 - menu.getSize().x / 2, window.getSize().y / 2 - menu.getSize().y / 2);

    auto nameText = sf::Text("ENTER YOUR NAME", font, 35);
    nameText.setPosition(sf::Vector2f(menu.getPosition().x + menu.getSize().x/2 - nameText.getGlobalBounds().width/2, menu.getPosition().y + 30));
    nameText.setFillColor(sf::Color::Magenta);

    auto username = std::string("");

    auto yourText = sf::Text(username, font, 50);

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if  (event.type == sf::Event::EventType::Closed) { window.close(); }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::Enter) {
                    if (username == "") username = "Abobus228";
                    leaderboards.saveResults(username, score);
                    return;
                }
                if (event.key.code == sf::Keyboard::Key::Escape) return;
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if ((event.text.unicode == '\b' && !username.empty())) username.pop_back();
                    else if(event.text.unicode != 32) username += static_cast<char>(event.text.unicode);

                }
            }
        }
            window.clear();
            window.draw(menu);
            window.draw(nameText);
            yourText.setString(username);
            yourText.setPosition(window.getSize().x / 2 - yourText.getGlobalBounds().width/2, nameText.getPosition().y + 150);
            window.draw(yourText);
            window.display();
    }
}
auto Game::restart() -> void{
    words = std::vector<std::vector<sf::Text>>();
    wave = std::pair<int, int>(0,5);
    textEntered = "";
    wordsSpeed = 0;
    score = 0;
}