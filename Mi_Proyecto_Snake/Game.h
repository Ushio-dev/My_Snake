#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>

#include "Snake.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	int m_size;
	Snake snake;
	void windowCollision();

	int w, h, n, m;

	int poins;
	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;


	sf::RectangleShape apple;
	sf::Vector2i m_item;

	sf::Clock time;

	int maxX, maxY;

	bool gameOver;

	void initApple();

	void initVariables();
	void initWindow();
	
	void initFonts();
	void initText();

public:
	Game();
	~Game();

	void updateGui();
	void renderGui(sf::RenderTarget* target);
	void respawnApple();
	bool running();
	void pollEvents();
	void update();
	void render();
};

