#pragma once
#include <cstdint>
#include <iostream>


#include "menu.h"
#include"SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "paddle.h"
#include "ball.h"


namespace windowparameters
{
    constexpr uint16_t RESOLUTION_X = 1280;
    constexpr uint16_t RESOLUTION_Y = 720;
    constexpr uint8_t COLOR_DEPTH = 32;
    constexpr uint16_t TIC_RATE_IN_MS = 60;
    constexpr uint8_t UNIT_SPACING = 32;
}
class gameManager
{
public:
    static void Start();

    

private:
    enum GameState { UNINITIALIZED, SHOWING_MENU, RUNNING, EXITING, GAMEOVER };

    static void GameLoop();
    static void ShowMenuScreen();
    static void InitializeGameElements();
    static void CleanupGameElements();
    static void HandleEvents();
    
    static GameState WaitForEnterOrExit();

    static GameState mGameState;
    static sf::RenderWindow mMainWindow;
};

