#pragma once

#include "LevelManager.h"
#include "EntityManager.h"
#include "GameStats.h"

#include "SFML/Graphics.hpp"
#include "../uis/UIManager.h"

#include <ctime>
#include <cstdlib>

enum class GameState
{
	MAIN_MENU,
	PLAYING,
	VICTORY,
	DEFEAT,
	PAUSED
};

class Game
{
public:

	Game();
	~Game();

	void run();

	void pollEvents();

	void centerWindow();

	void updateGameGraphics();
	void drawGameGraphics();

	int getSeed() const;

private:

	// Internal init methods
	void initGraphics();
	void initViews();

	void shutDown();

private:

	// Window
	sf::RenderWindow m_window;
	const sf::Vector2u m_LOGICAL_RESOLUTION = { 1920, 1080 }; // Resolution used to calculate everything in game (the sf::View will dynamically resize the game depending on the window size)

	// Frames
	sf::Clock m_deltaClock;
	float m_deltatime = 0.f;
	const int m_FRAME_RATE = 60;

	// View
	sf::View m_gameView;

	// Seed
	int m_seed = -1;

	// Managers
	std::unique_ptr<EntityManager> m_entityManager = nullptr;
	std::unique_ptr<LevelManager> m_levelManager = nullptr;
	std::unique_ptr<GameStats> m_gameStats = nullptr;
	std::unique_ptr<UIManager> m_uiManager = nullptr;

	// Game State
	GameState m_gameState = GameState::PLAYING;

	// Graphics
	sf::Texture m_conveyorTexture;
	sf::Texture m_fireTexture;
	sf::Texture m_factoryTexture;

	sf::Sprite m_conveyorSprite1;
	sf::Sprite m_conveyorSprite2;
	sf::Sprite m_fireSprite;
	sf::Sprite m_factorySprite; // Game background
};