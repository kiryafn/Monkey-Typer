#include "LeaderBoards.h"

auto Leaderboards::sortByScore() -> void {
    file = std::fstream("leaderboard.txt",std::ios::in | std::ios::out);

    auto vec = std::vector<std::string>();
    auto str = std::string();

    while (std::getline(file, str)) {
        vec.push_back(str);
    }

    std::ranges::sort(vec, [](std::string f, std::string s) {
        auto firstNumber = std::string(f.begin(), std::ranges::find(f, ' '));
        auto secondNumber = std::string(s.begin(), std::ranges::find(s, ' '));
        return std::stoi(firstNumber) > std::stoi(secondNumber);});

    //clean list
    file = std::fstream("leaderboard.txt",std::ios::out | std::ios::trunc);
    file = std::fstream("leaderboard.txt",std::ios::in | std::ios::out);


    auto itr = vec.begin();
    for (int i = 0; i < vec.size(); i++) {
        file << *itr << "\n"; //pPROBLEMBLYA
        itr++;
    }
}

auto Leaderboards::showLeaders() -> void {

    auto menu = Shape(sf::Vector2f (window.getSize().x / 2, window.getSize().y / 2), sf::Color::Black, 0,0, 10, sf::Color::Magenta);
    menu.setPosition(window.getSize().x / 2 - menu.getSize().x / 2, window.getSize().y / 2 - menu.getSize().y / 2);

    auto nameText = sf::Text("Name", font, 35);
    nameText.setPosition(sf::Vector2f(window.getSize().x / 3 + 50, window.getSize().y / 4));
    nameText.setFillColor(sf::Color::Magenta);

    auto scoreText = sf::Text("Score", font, 35);
    scoreText.setPosition(sf::Vector2f(window.getSize().x - window.getSize().x / 2 + 100, window.getSize().y / 4));
    nameText.setFillColor(sf::Color::Magenta);
///----------------------------------------------------------------------------------------------------------------------------------------
    while (window.isOpen()) {
        auto event = sf::Event();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {window.close();}
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape) return;
        }

        window.draw(menu);
        window.draw(nameText);
        window.draw(scoreText);
        updateValues(menu, nameText, scoreText);   /// data from txt file
        window.display();
    }
}

auto Leaderboards::saveResults(std::string name, int score) -> void {
    file = std::fstream("leaderboard.txt",std::ios::app);
    file << score << " " << name << "\n";
    sortByScore();
}

auto Leaderboards::updateValues(Shape &menu, sf::Text &nameText, sf::Text &scoreText) -> void {
    file = std::fstream("leaderboard.txt",std::ios::in | std::ios::out);
    auto data = std::string();
    auto y = nameText.getPosition().y + 60;
    auto text = sf::Text(data, font, 35);
    auto scoreBool = true;


    while (file >> data) {
       if (y > menu.getPosition().y + menu.getSize().y - 10) break;

        text.setString(data);
        text.setFillColor(sf::Color::White);

        if (scoreBool) text.setPosition(scoreText.getPosition().x, y);
        else text.setPosition(nameText.getPosition().x, y);

        scoreBool = !scoreBool;
        window.draw(text);

        if (scoreBool) y += 60;
    }
    file.clear();
    file.seekg(0);
}
