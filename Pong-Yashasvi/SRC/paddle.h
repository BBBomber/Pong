#pragma once
#include<sstream>
#include <SFML/Graphics.hpp>


class paddle
{
private:
	sf::RectangleShape paddleShape;
	sf::Vector2f paddlePos;
	float speed = 1100.0f;

	

	bool leftMove = false;
	bool rightMove = false;

public:
	paddle(float x, float y);
	
	sf::RectangleShape getShape();
	sf::FloatRect getPos();

	int lives = 5;
	int onLose();
	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();
	
	void update(sf::Time dt);

};

