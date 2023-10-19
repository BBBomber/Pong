#include "paddle.h"


paddle::paddle(float x, float y)
{
	paddlePos.x = x;
	paddlePos.y = y;

	paddleShape.setSize(sf::Vector2f(50, 5));
	paddleShape.setFillColor(sf::Color::Red);
	paddleShape.setOutlineColor(sf::Color::Magenta);
	paddleShape.setOutlineThickness(3);


	paddleShape.setPosition(paddlePos);
	
}

sf::FloatRect paddle::getPos()
{
	return paddleShape.getGlobalBounds();
}

sf::RectangleShape paddle::getShape()
{
	return paddleShape;
}

void paddle::moveLeft()
{
	leftMove = true;
}
void paddle::moveRight()
{
	rightMove = true;
}

void paddle::stopLeft()
{
	leftMove = false;
}

void paddle::stopRight()
{
	rightMove = false;
}
int paddle::onLose()
{
	lives--;
	return lives;
}



void paddle::update(sf::Time dt)
{
	if (leftMove)
	{
		paddlePos.x -= speed * dt.asSeconds();

	}

	if (rightMove)
	{
		paddlePos.x += speed * dt.asSeconds();
	}

	paddleShape.setPosition(paddlePos);
}