#include "menu.h"


menu::menu(sf::RenderWindow& window) : window(window) {
    if (!font.loadFromFile("SRC/Fonts/PixelEmulator.otf")) {
        // Handle font loading error
    }
    if (!texture.loadFromFile("SRC/music/pong_image.png" ))
    {
        // error...
    }
    
    
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(24);
    playText.setFillColor(sf::Color::White);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);

    playButton.setSize(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color(0, 128, 0));
    playButton.setPosition(100, 100);

    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(128, 0, 0));
    exitButton.setPosition(100, 200);

    playClicked = false;
    exitClicked = false;
}

menu::~menu() {
    // Clean up any resources if needed
}

void menu::handleEvents(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            playClicked = true;
        }
        else if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            exitClicked = true;
        }
    }
}

void menu::render() {

    sf::Vector2f targetSize(1280.0f, 720.0f);

    
    sf::Sprite sprite(texture);
    sprite.setScale(
        targetSize.x / sprite.getLocalBounds().width,
        targetSize.y / sprite.getLocalBounds().height);
    window.clear(sf::Color::Black);
    window.draw(sprite);
    window.draw(playButton);
    window.draw(exitButton);

    playText.setPosition(playButton.getPosition().x + 60, playButton.getPosition().y + 10);
    window.draw(playText);

    exitText.setPosition(exitButton.getPosition().x + 60, exitButton.getPosition().y + 10);
    window.draw(exitText);

    window.display();
}