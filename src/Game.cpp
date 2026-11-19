
#include "Game.h"
#include "Tile.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  
}

Game::~Game()
{
    
}

bool Game::init()
{
    
    current_state = MENU;
    board = std::make_shared<Board>(window);
    board->init();   

    if (!font.openFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "font failed too load" << std::endl;
    }

    hostText.setString("Host");
    hostText.setCharacterSize(50);
    hostText.setFillColor(sf::Color::White);
    hostText.setPosition({ 1000.f, 50.f });

    joinText.setString("Join");
    joinText.setCharacterSize(50);
    joinText.setFillColor(sf::Color::White);
    joinText.setPosition({ 1000.f, 125.f });

    return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
    board->render(); 
    window.draw(hostText);
    window.draw(joinText);
}

void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
    if (current_state == MENU)
    {
        if (hostText.getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            current_state = GAME;
            std::cout << " Creating Server" << std::endl;
            server = std::make_unique<Server>();
            server->init();
            server->run();
        }
        else if (joinText.getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            current_state = GAME;
            std::cout << "Attempting to connect to Server" << std::endl;
            client = std::make_unique<Client>();
            client->connect();
        }
    }


    board->mouseButtonPressed(event);
}

void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
    board->mouseButtonReleased(event);    
}

void Game::keyPressed(const sf::Event::KeyPressed* event)
{

}

void Game::keyReleased(const sf::Event::KeyReleased* event)
{

}

void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
    board->mouseMoved(event);
}




