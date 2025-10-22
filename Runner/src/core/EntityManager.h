#pragma once
#include <iostream>
#include "../models/Player.h"
#include "SFML/Graphics.hpp"
#include "MathsLib/Vector2.h"
#include <Vector>


//class Obstacle;

class EntityManager
{
public:

	EntityManager();
	~EntityManager();


	void updateAll(float deltatime);
	void drawAll(sf::RenderWindow& window);
	
	void updateColisions();
	void spawnEntity(int entityUID, math::Vector2<float> position);


private:
	/*std::vector<std::unique_ptr<Obstacle>> m_obstacles;*/
	std::unique_ptr<Player> m_player;
};