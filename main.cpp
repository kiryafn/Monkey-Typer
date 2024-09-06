#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Leaderboards.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(1920, 1080), "MONKEY TYPER");
    Savings savings = Savings(window, "Montserrat-SemiBold.ttf");
    Leaderboards leaderboards = Leaderboards(window, "Montserrat-SemiBold.ttf");
    Settings settings = Settings(window, "Montserrat-SemiBold.ttf", leaderboards, savings);
    Game game = Game(window, "Arcade.ttf", settings, leaderboards, savings);
    game.showGame();
}
