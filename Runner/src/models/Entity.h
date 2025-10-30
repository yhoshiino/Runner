#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../core/GameStats.h"

class Entity 
{
public:

	Entity(GameStats* gameStats, sf::Vector2f spawnPosition);
	Entity(GameStats* gameStats);

	virtual ~Entity();

	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);

	virtual bool isColliding(sf::FloatRect otherHitbox, float deltaTime);
	virtual void onHit(Entity * otherEntity);

	void setPosition(sf::Vector2f newPos);
	void addVelocity(sf::Vector2f newVelocity);

	sf::Vector2f getPosition() const;
	sf::Vector2f getPreviousPosition() const;
	float getConveyorSpeed() const;
	sf::FloatRect getHitbox() const;
	
	bool isActive() const;

protected:

	GameStats* m_gameStats;

	sf::Vector2f m_position = { 0.f, 0.f };
	sf::Vector2f m_previousPosition = { 0.f, 0.f }; // Used for the CCD algorithm (Continuous Collision Detection)
	sf::Vector2f m_velocity = { 0.f, 0.f };
	sf::FloatRect m_hitbox;

	sf::RectangleShape m_square; // For debugging

	int m_health = 5;

	const float m_SIZE = 72.f;
	bool m_isActive = false;

	enum class State 
	{
		ALIVE,
		DEAD
	};

	State m_state = State::ALIVE;
};