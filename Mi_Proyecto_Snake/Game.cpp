#include "Game.h"

void Game::windowCollision()
{
	// Left
	if (this->snake.getPos().x < 0) 
		this->snake.setPos(sf::Vector2i(this->maxX + 1, this->snake.getPos().y));	
	// Right
	if (this->snake.getPos().x > this->maxX + 1)
		this->snake.setPos(sf::Vector2i(0, this->snake.getPos().y));
	// Top
	if (this->snake.getPos().y < 0)
		this->snake.setPos(sf::Vector2i(this->snake.getPos().x, this->maxY + 1));
	// Bottom
	if (this->snake.getPos().y > this->maxY + 1)
		this->snake.setPos(sf::Vector2i(this->snake.getPos().x, 0));
}

void Game::initApple()
{
	this->apple.setSize(sf::Vector2f(16, 16));
	this->apple.setFillColor(sf::Color::Red);
	this->maxX = (this->window->getSize().x / 16) - 2;
	this->maxY = (this->window->getSize().y / 16) - 2;
	this->m_item = sf::Vector2i(
		rand() % maxX + 1,
		rand() % maxY + 1
	);
	this->apple.setPosition(
		m_item.x * 16,
		m_item.y * 16
	);
}

void Game::initVariables()
{
	this->w = 40;
	this->h = 25;
	this->window = NULL;
	this->time.restart();

	this->m_size = 16;

	this->poins = 0;
	this->gameOver = false;
}


void Game::initWindow()
{
	this->videoMode.width = this->w * 16;
	this->videoMode.height = this->h * 16;

	this->window = new sf::RenderWindow(this->videoMode, "Snake");
	n = (this->window->getSize().x / m_size);
	m = (this->window->getSize().y / m_size);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "Error::GAme::InitFont";
}

void Game::initText()
{
	// gui Text
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(24);
	this->guiText.setString("Test");

	// End Game Text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(225, 100));
	this->endGameText.setString("PERDISTE");
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initApple();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}


void Game::updateGui()
{
	std::stringstream ss;


	ss << "Points: " << this->poins;
	this->guiText.setString(ss.str());
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::respawnApple()
{
	if (this->snake.getPos() == this->m_item) {
		this->snake.extend();
		initApple();
		this->poins += 10;
	}
}

bool Game::running()
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	sf::Event ev;

	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				this->window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->snake.getDirection() != Direction::Dowm)
				this->snake.setDirection(Direction::Up);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->snake.getDirection() != Direction::Left)
				this->snake.setDirection(Direction::Right);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->snake.getDirection() != Direction::Up)
				this->snake.setDirection(Direction::Dowm);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->snake.getDirection() != Direction::Right)
				this->snake.setDirection(Direction::Left);
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
	if (this->gameOver == false)
	{
		if (time.getElapsedTime().asSeconds() >= 0.1) {
			this->respawnApple();
			this->snake.update();
			this->windowCollision();
			if (this->snake.checkCollision())
				this->gameOver = true;
			this->updateGui();
			time.restart();
		}
	}
}

void Game::render()
{
	this->window->clear(sf::Color::Black);
	this->snake.render(*this->window);
	this->window->draw(this->apple);
	this->renderGui(this->window);

	if (this->gameOver)
		this->window->draw(this->endGameText);
	this->window->display();
}
