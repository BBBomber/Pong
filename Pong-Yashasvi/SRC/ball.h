#pragma once
#include <SFML/Graphics.hpp>

class ball
{
private:
	sf::Vector2f ballPos;
	sf::RectangleShape ballShape;

	float speed = 360;
	float dirX = 1.0f;
	float dirY = 1.0f;

public:
	ball(float x, float y);

	sf::FloatRect getPos();
	sf::RectangleShape getShape();

	float getXVelocity();

	void bounceSide();

	void missTop();

	void missBottom();

	void hitBall();

	void update(sf::Time dt);
};

