#pragma once
#include <iostream>
#include <vector>

#include "../models/Player.h"
#include "../models/Collectible.h"

#include "SFML/Graphics.hpp"

class EntityManager
{
public:

	EntityManager(GameStats* gameStatsRef);
	~EntityManager();

	void updateAll(float deltaTime);
	void updateColisions(float deltaTime);
	void applyPlayerMovement(float deltaTime);
	void drawAll(sf::RenderWindow& window);

	void spawnEntity(sf::Vector2f position);
	void spawnCollectible(sf::Vector2f position, char uid);
	void spawnEntity(std::unique_ptr<Entity> entityPtr);

	void spawnEntitiesRandomly(int entitiesToSpawn, float deltaTime);

	void resetPlayerPosition();

private:
	GameStats* m_gameStats;

	std::vector<std::unique_ptr<Entity>> m_gameObjects;
	std::unique_ptr<Player> m_player;
};