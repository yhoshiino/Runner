#pragma once

#include "SFML/Graphics.hpp"
#include "Vector2.h"

class Game
{
public:

private:

	sf::RenderWindow m_window;

	sf::Clock m_deltaClock;
	float m_deltatime;

	const int m_FRAME_RATE = 60;

};

