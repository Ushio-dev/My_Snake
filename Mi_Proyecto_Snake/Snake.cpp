#include "Snake.h"

void Snake::initSnake()
{
	m_size = 16;
	this->body.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	snakeBody.push_back(SnakeSegment(5, 7));
	snakeBody.push_back(SnakeSegment(5, 6));
	snakeBody.push_back(SnakeSegment(5, 5));
	this->dir = Direction::None;
}

void Snake::move()
{
	if (this->dir != Direction::None)
	{
		for (int i = snakeBody.size() - 1; i > 0; --i)
		{
			snakeBody[i].position = snakeBody[i - 1].position;
		}
	}
	
	switch (this->dir)
	{
	case Direction::Up:
		--this->snakeBody[0].position.y;
		break;
	case Direction::Dowm:
		++this->snakeBody[0].position.y;
		break;
	case Direction::Right:
		++this->snakeBody[0].position.x;
		break;
	case Direction::Left:
		--this->snakeBody[0].position.x;
		break;
	default:
		this->snakeBody[0].position += sf::Vector2i(0, 0);
		break;
	}
}

Snake::Snake()
{
	this->initSnake();
}

Snake::~Snake()
{
	
}

void Snake::setDirection(Direction l_dir)
{
	this->dir = l_dir;
}

Direction Snake::getDirection()
{
	return this->dir;
}

void Snake::tick()
{
	move();
}

void Snake::extend()
{
	auto tail = this->snakeBody[this->snakeBody.size() - 1];

	switch (this->dir)
	{
	case Direction::Dowm:
		tail.position = sf::Vector2i(tail.position.x + 1, tail.position.y + 1);
		break;
	case Direction::Right:
		tail.position = sf::Vector2i(tail.position.x + 1, tail.position.y + 1);
		break;
	case Direction::Up:
		tail.position = sf::Vector2i(tail.position.x - 1, tail.position.y - 1);
		break;
	case Direction::Left:
		tail.position = sf::Vector2i(tail.position.x - 1, tail.position.y - 1);
		break;
	}
	
	this->snakeBody.push_back(tail);

}

bool Snake::checkCollision()
{
	for (int i = 1; i < this->snakeBody.size(); i++)
	{
		if (this->snakeBody[0].position == this->snakeBody[i].position)
			return true;
	}

	return false;
}

sf::Vector2i Snake::getPos()
{
	return this->snakeBody[0].position;
}

void Snake::setPos(sf::Vector2i l_pos)
{
	this->snakeBody[0].position = l_pos;
}

bool Snake::appleIn(sf::Vector2i applePos)
{
	int i = 0;
	while (i < this->snakeBody.size())
	{
		if (this->snakeBody[i].position == applePos) {
			std::cout << "ups toque body";
			return true;
		}
		else
			i++;
	} 	

	return false;
}

void Snake::update()
{
	this->tick();
}

void Snake::render(sf::RenderTarget& target)
{
	auto head = snakeBody.begin();
	this->body.setFillColor(sf::Color::Yellow);
	this->body.setPosition(head->position.x * m_size, head->position.y * m_size);
	target.draw(this->body);

	this->body.setFillColor(sf::Color::Green);
	for (auto i = snakeBody.begin() + 1; i != snakeBody.end(); i++)
	{
		this->body.setPosition(i->position.x * m_size, i->position.y * m_size);
		target.draw(this-> body);
	}
}
