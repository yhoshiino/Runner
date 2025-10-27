#pragma once
#include <iostream>
#include <vector>

#include "../models/Player.h"
#include "SFML/Graphics.hpp"

class EntityManager
{
public:

	EntityManager(GameStats* gameStatsRef);
	~EntityManager();

	void updateAll(float deltaTime);
	void drawAll(sf::RenderWindow& window);
	
	void updateColisions(float deltaTime);
	void applyPlayerMovement();
	void spawnEntity(int entityUID, sf::Vector2f position);

	void resetPlayerPosition();

private:
	GameStats* m_gameStats;

	std::vector<std::unique_ptr<Entity>> m_obstacles;
	std::unique_ptr<Player> m_player;
};