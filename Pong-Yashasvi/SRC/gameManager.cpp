
#include "gameManager.h"
#include "SFML/Audio.hpp"

namespace
{
    ball* gameBall;
    paddle* p1Paddle;
    sf::Clock* gameClock;
    paddle* p2Paddle;
    sf::Font font;
    float bouncetimer;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    
}

void gameManager::Start()
{
    font.loadFromFile("SRC/Fonts/PixelEmulator.otf");
    
    if (!soundBuffer.loadFromFile("SRC/music/244656__greenvwbeetle__pop-6.wav")) {
        // Handle loading error
       
    }
    sound.setBuffer(soundBuffer);
    if (mGameState != UNINITIALIZED)
        return;

    mMainWindow.create(sf::VideoMode(windowparameters::RESOLUTION_X, windowparameters::RESOLUTION_Y, windowparameters::COLOR_DEPTH), "Pong!");
    
    mGameState = SHOWING_MENU;

    while (mGameState != EXITING)
        GameLoop();

    mMainWindow.close();
}

void gameManager::ShowMenuScreen()
{

    menu mainMenu(mMainWindow);

    while (mGameState == SHOWING_MENU)
    {
        
        sf::Event event;
        while (mMainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mGameState = EXITING;
                mMainWindow.close();
            }
            else
            {
                
                mainMenu.handleEvents(event);
            }
        }

        
        mainMenu.render();

        if (mainMenu.isPlayClicked())
        {
            
            mGameState = RUNNING;
        }
        else if (mainMenu.isExitClicked())
        {
            
            mGameState = EXITING;
        }
    }
    
}

gameManager::GameState gameManager::WaitForEnterOrExit()
{
    GameState nextstate = GAMEOVER;
    sf::Event currentevent;

    sf::Text fontHUD1; 
    fontHUD1.setFont(font);
    fontHUD1.setPosition(1280 / 2, 720 / 2);
    fontHUD1.setCharacterSize(60);
    fontHUD1.setFillColor(sf::Color::Green);

    while (nextstate != EXITING && nextstate != RUNNING)
    {
        while (mMainWindow.pollEvent(currentevent))
        {
            std::stringstream ss;
            if (p2Paddle->lives > 0)
            {
                ss << "Player 2 WINS!";
            }
            else {
                ss << "Player 1 WINS!";
            }
            fontHUD1.setString(ss.str());

            if (currentevent.type == sf::Event::EventType::KeyPressed &&
                currentevent.key.code == sf::Keyboard::Enter) 
            {
                nextstate = RUNNING;
            }
            else if (currentevent.type == sf::Event::EventType::Closed)
            {
                nextstate = EXITING;
            }
        }

        mMainWindow.clear(); 
        mMainWindow.draw(fontHUD1);
        mMainWindow.display(); 
    }

    return nextstate;
}

void gameManager::InitializeGameElements()
{
    
    gameBall = new ball(1280 / 2, 0);
    gameClock = new sf::Clock();
    p1Paddle = new paddle(1280 / 2, 710);
    p2Paddle = new paddle(1280 / 2, 10);
    
    bouncetimer = 0.10f;
   
}
void gameManager::CleanupGameElements()
{
    delete(gameClock);
    delete(gameBall);
    delete(p1Paddle);
    delete(p2Paddle);
}

void gameManager::HandleEvents()
{
    
    
    std::stringstream ss;
    sf::Time dt;
    dt = gameClock->restart();
    bouncetimer -= dt.asSeconds();
    sf::Text fontHUD;
    fontHUD.setFont(font);
    fontHUD.setPosition(0, 700);
    fontHUD.setCharacterSize(15);
    fontHUD.setFillColor(sf::Color::Green);
    ss << "Lives: " << p1Paddle->lives;
    fontHUD.setString(ss.str());
    
    
    std::stringstream sss;
    sf::Text fontHUD1;
    fontHUD1.setFont(font);
    fontHUD1.setPosition(0, 10);
    fontHUD1.setCharacterSize(15);
    fontHUD1.setFillColor(sf::Color::Red);
    sss << "Lives: " << p2Paddle->lives;
    fontHUD1.setString(sss.str());
    

    if (gameBall->getPos().intersects(p1Paddle->getPos()) || gameBall->getPos().intersects(p2Paddle->getPos()))
    {

        
        if (bouncetimer < 0)
        {
            sound.play();
            gameBall->hitBall();
            bouncetimer = 0.10f;
        }
        
                    
    }
         

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        p1Paddle->moveLeft();
    }
    else
    {
        p1Paddle->stopLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        p1Paddle->moveRight();
    }
    else
    {
        p1Paddle->stopRight();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        p2Paddle->moveLeft();
    }
    else
    {
        p2Paddle->stopLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        p2Paddle->moveRight();
    }
    else
    {
        p2Paddle->stopRight();
    }



    if (gameBall->getPos().left < 0 || gameBall->getPos().left + gameBall->getPos().width > 1280)
    {
                gameBall->bounceSide();
    }
    if (gameBall->getPos().top < 0)
    {
                gameBall->missTop();
                
                if (p2Paddle->onLose() <=0)
                {
                    mGameState = GAMEOVER;
                }
                
                
    }

    if (gameBall->getPos().top + gameBall->getPos().height > 720)
    {

        gameBall->missBottom();
        
        if (p1Paddle->onLose() <= 0)
        {
            mGameState = GAMEOVER;
        }
       
        

       
    }

        
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
            mGameState = EXITING;
            mMainWindow.close();
    }

        
    
    
    mMainWindow.clear();
    mMainWindow.draw(gameBall->getShape());
    mMainWindow.draw(p1Paddle->getShape());
    mMainWindow.draw(p2Paddle->getShape());
    
    mMainWindow.draw(fontHUD);
    mMainWindow.draw(fontHUD1);

    gameBall->update(dt);
    p1Paddle->update(dt);
    p2Paddle->update(dt);
    
    mMainWindow.display();
    
    
}




void gameManager::GameLoop() //state controller
{
    while (true)
    {
        switch (mGameState)
        {
        case SHOWING_MENU:
            ShowMenuScreen();
            break;

        case GAMEOVER:
            mGameState = WaitForEnterOrExit();
            break;

        case RUNNING:

            InitializeGameElements();

            // run game loop
            while (mMainWindow.isOpen() && mGameState == RUNNING)
            {
                HandleEvents();
                
            }

            CleanupGameElements();
            break;

        case EXITING:
            mMainWindow.close();
            break;

        default:
            mMainWindow.close();
            break;
        }
    }
}


gameManager::GameState gameManager::mGameState = gameManager::UNINITIALIZED;
sf::RenderWindow gameManager::mMainWindow;