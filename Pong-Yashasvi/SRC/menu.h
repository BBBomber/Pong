#pragma once

#include <SFML/Graphics.hpp>

class menu {
public:
    menu(sf::RenderWindow& window);
    ~menu();
    
    void handleEvents(sf::Event& event);
    void render();
    sf::Texture texture;
    bool isPlayClicked() { return playClicked; }
    bool isExitClicked() { return exitClicked; }

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text playText;
    sf::Text exitText;
    sf::RectangleShape playButton;
    sf::RectangleShape exitButton;
    bool playClicked;
    bool exitClicked;
};