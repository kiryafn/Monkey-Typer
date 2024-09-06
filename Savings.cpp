#include "Savings.h"
#include "Game.h"

auto Savings::showSavings() -> void {
    auto menu = Shape(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Color::Black, 0, 0, 10,
                      sf::Color::Green);
    menu.setPosition(window.getSize().x / 2 - menu.getSize().x / 2, window.getSize().y / 2 - menu.getSize().y / 2);

    auto savings = sf::Text("Savings", font, 35);
    savings.setPosition(sf::Vector2f(menu.getPosition().x + menu.getSize().x / 2 - savings.getGlobalBounds().width / 2,
                                     menu.getPosition().y + 30));
    savings.setFillColor(sf::Color::Green);

    auto save1 = sf::Text("", font, 35);
    auto save1Button = sf::RectangleShape(sf::Vector2f(menu.getSize().x / 1.5f, 50));
    save1Button.setPosition(sf::Vector2f(menu.getPosition().x + menu.getSize().x / 2 - save1Button.getSize().x / 2,
                                         savings.getPosition().y + savings.getGlobalBounds().height + 60));
    save1Button.setFillColor(sf::Color::Black);
    save1Button.setOutlineColor(sf::Color::Green);
    save1Button.setOutlineThickness(2.5f);
    save1.setPosition(sf::Vector2f(save1Button.getPosition().x, save1Button.getPosition().y));

    auto save2Button = sf::RectangleShape(sf::Vector2f(menu.getSize().x / 1.5f, 50));
    save2Button.setPosition(sf::Vector2f(save1Button.getPosition().x, save1Button.getPosition().y + save1Button.getSize().y + 35));
    save2Button.setFillColor(sf::Color::Black);
    save2Button.setOutlineColor(sf::Color::Green);
    save2Button.setOutlineThickness(2.5f);

    auto save2 = sf::Text("", font, 35);
    save2.setPosition(sf::Vector2f(save2Button.getPosition().x, save2Button.getPosition().y));

    auto save3Button = sf::RectangleShape(sf::Vector2f(menu.getSize().x / 1.5f, 50));
    save3Button.setPosition(sf::Vector2f(save1Button.getPosition().x, save2Button.getPosition().y + save2Button.getSize().y + 35));

    save3Button.setFillColor(sf::Color::Black);
    save3Button.setOutlineColor(sf::Color::Green);
    save3Button.setOutlineThickness(2.5f);
    auto save3 = sf::Text("", font, 35);
    save3.setPosition(sf::Vector2f(save3Button.getPosition().x, save3Button.getPosition().y));

    updateValues(save1,save2,save3);

///----------------------------------------------------------------------------------------------------------------------------------------
    while (window.isOpen()) {
        auto event = sf::Event();
        auto mouse = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape) return;
            else if (event.type == sf::Event::MouseButtonPressed) {
                auto info = takeData();

                if (save1Button.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    Game::score = info[0][0];
                    Game::wave.first = info[0][1] - 1;             ///wave.first++ AND IT MAKES A WAVE 1 BIGGER BUT IF ZERO IT IS OKAY
                    Game::words = std::vector<std::vector<sf::Text>>();///SO TO FIX THIS I SUBSTRACT 1 IF I WANT TO LOAD NON ZERO WAVE
                    return;
                }
                if (save2Button.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    Game::score = info[1][0];
                    Game::wave.first = info[1][1] - 1;
                    Game::words = std::vector<std::vector<sf::Text>>();
                    return;
                }
                if (save3Button.getGlobalBounds().contains(mouse.x, mouse.y)) {
                    Game::score = info[2][0];
                    Game::wave.first = info[2][1] - 1;
                    Game::words = std::vector<std::vector<sf::Text>>();
                    return;
                }
            }
            window.draw(menu);
            window.draw(savings);
            window.draw(save1Button);
            window.draw(save1);
            window.draw(save2Button);
            window.draw(save2);
            window.draw(save3Button);
            window.draw(save3);
            window.display();
        }
    }
}

auto Savings::saveResults(int score, int wave) -> void {

    file = std::fstream("saves.txt",std::ios::in | std::ios::out);

    auto vec = std::vector<std::string>();
    auto str = std::string();

    while (std::getline(file, str)) {
        vec.push_back(str);
    }

    std::string toWriteOne = std::to_string(score) + " " + std::to_string(wave) + " " + "1";
    std::string toWriteZero= std::to_string(score) + " " + std::to_string(wave) + " " + "0";

    if (!save1) {
        vec[0] = toWriteOne;
        save1 = true;
    }
    else if (!save2) {
        vec[1] = toWriteOne;
        save2 = true;
    }
    else if (!save3) {
        vec[2] = toWriteOne;
        save3 = true;
    }
    else{
        save1 = false;
        vec[0] = toWriteOne;
        save2 = false;
        vec[1][vec[1].size()-1] = '0';
        save3 = false;
        vec[2][vec[2].size()-1] = '0';
    }

    //clean list
    file = std::fstream("saves.txt",std::ios::out | std::ios::trunc);
    file = std::fstream("saves.txt",std::ios::in | std::ios::out);


    auto itr = vec.begin();
    for (int i = 0; i < vec.size(); i++) {
        file << *itr << "\n";
        itr++;
    }
}

auto Savings::takeData() -> std::vector<std::vector<int>>{
    std::vector<std::vector<int>> dataMass = {{0,0,0},{0,0,0},{0,0,0}};
    std::string data = std::string();

    file = std::fstream("saves.txt",std::ios::in | std::ios::out);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            file >> data;
            int tmp = std::stoi(data);
            dataMass[i][j] = tmp;
        }
    }
    return dataMass;
}

auto Savings::updateValues(sf::Text& s1, sf::Text& s2, sf::Text& s3) -> void {
    file = std::fstream("saves.txt",std::ios::in | std::ios::out);
    auto data = std::string();


    std::getline(file,data);
    if (data[data.size()-1] == '1') save1 = true;
    else save1 = false;
    s1.setString("Score and wave: " + data + "-status");

    std::getline(file,data);
    if (data[data.size()-1] == '1') save2 = true;
    else save2 = false;
    s2.setString("Score and wave: " + data + "-status");

    std::getline(file,data);
    if (data[data.size()-1] == '1') save3 = true;
    else save3 = false;
    s3.setString("Score and wave: " + data + "-status");

    file.clear();
    file.seekg(0);
}
