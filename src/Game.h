
#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Server.h"
#include "Client.h"

class Game
{
 public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
	void keyPressed(const sf::Event::KeyPressed* event);
	void keyReleased(const sf::Event::KeyReleased* event);
	void mouseMoved(const sf::Event::MouseMoved* event);
	std::unique_ptr<Server> server;
	std::unique_ptr<Client> client;

	sf::Font font;
	sf::Text hostText = sf::Text(font);
	sf::Text joinText = sf::Text(font);

	

 private:

	 enum GameState
	 {
		 MENU,
		 GAME
	 };
	GameState current_state;
	sf::RenderWindow& window;
	std::shared_ptr<Board> board;
};

