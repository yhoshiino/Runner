#pragma once
#include <iostream>
#include <vector>

#include "../models/Player.h"
#include "SFML/Graphics.hpp"


//class Obstacle;

class EntityManager
{
public:

	EntityManager();
	~EntityManager();


	void updateAll(float deltatime);
	void drawAll(sf::RenderWindow& window);
	
	void updateColisions();
	void spawnEntity(int entityUID, sf::Vector2f position);

	void resetPlayerPosition();

private:
	/*std::vector<std::unique_ptr<Obstacle>> m_obstacles;*/
	std::unique_ptr<Player> m_player;
};