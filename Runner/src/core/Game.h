#pragma once

#include "LevelManager.h"

#include "SFML/Graphics.hpp"

//class EntityManager;

class Game
{
public:

	Game();
	~Game();

	void run();

	void pollEvents();

	void centerWindow();

private:

	sf::RenderWindow m_window;

	sf::Clock m_deltaClock;
	float m_deltatime = 0.f;

	const int m_FRAME_RATE = 60;
	const sf::Vector2u m_logicalResolution = {1920, 1080};

	//std::unique_ptr<EntityManager> m_entityManager;
	std::unique_ptr<LevelManager> m_levelManager;

	sf::View m_gameView;

private:

	void shutDown();
};