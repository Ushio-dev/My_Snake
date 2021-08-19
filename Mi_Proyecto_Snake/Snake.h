#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

enum class Direction
{
	None,
	Up,
	Dowm,
	Right,
	Left
};

class Snake
{
private:
	sf::RectangleShape body;
	std::vector<SnakeSegment> snakeBody;
	void initSnake();
	int m_size;
	int n, m;

	void move();
	Direction dir;
	
public:
	Snake();
	~Snake();

	void setDirection(Direction l_dir);
	Direction getDirection();
	void tick();
	void extend();
	bool checkCollision();
	sf::Vector2i getPos();
	void setPos(sf::Vector2i l_pos);
	
	bool appleIn(sf::Vector2i applePos);

	void update();
	void render(sf::RenderTarget& target);
};

