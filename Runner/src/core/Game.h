#pragma once

#include "LevelManager.h"
#include "EntityManager.h"
#include "GameStats.h"

#include "SFML/Graphics.hpp"
#include "../uis/UIManager.h"

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

	std::unique_ptr<EntityManager> m_entityManager = nullptr;
	std::unique_ptr<LevelManager> m_levelManager = nullptr;
	std::unique_ptr<GameStats> m_gameStats = nullptr;

	sf::View m_gameView;

private:
	UIManager m_uiManager;

	void initViews();
	void shutDown();
};