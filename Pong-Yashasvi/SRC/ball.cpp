#include "ball.h"


ball::ball(float x, float y)
{
	ballPos.x = x;
	ballPos.y = y;

	ballShape.setSize(sf::Vector2f(10, 10));
	ballShape.setPosition(ballPos);


}


sf::FloatRect ball::getPos()
{
	return ballShape.getGlobalBounds();

}

sf::RectangleShape ball::getShape()
{
	return ballShape;
}

float ball::getXVelocity()
{
	return dirX;
}

void ball::bounceSide()
{
	dirX = -dirX;
}

void ball::missTop()
{
	
	ballPos.x = 1280 / 2;
	ballPos.y = 720/2; //bottom of screen
	
	
}

void ball::missBottom()
{
	
	ballPos.x = 1280 / 2; //since 1280 is the left we set it at the center
	ballPos.y = 720/2; //top of the screen since 0 is top
	
}

void ball::hitBall()
{
	dirY = -dirY;
}

void ball::update(sf::Time dt)
{
	ballPos.x += dirX * speed * dt.asSeconds();
	ballPos.y += dirY * speed * dt.asSeconds();

	ballShape.setPosition(ballPos);

}