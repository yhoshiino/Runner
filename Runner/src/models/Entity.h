#pragma once
#include "MathsLib/Vector2.h"
#include <SFML/Graphics.hpp>

class Entity 
{
public:

	Entity(math::Vector2<float> spawnPosition, math::Vector2<float> initialVelocity);
	Entity() = default;

	virtual ~Entity();

	virtual void update(float deltatime);
	virtual void draw(sf::RenderWindow& window);

	virtual bool isColliding(sf::FloatRect otherHitbox);
	virtual void onHit(Entity * otherEntity);

private:

	
	math::Vector2<float> m_position = {0.f,0.f};
	math::Vector2<float> m_velocity = { 1.f,1.f };

	int m_health = 5;
	const float m_SIZE = 64.f;

	sf::FloatRect m_hitbox;

	enum class State 
	{
		ALIVE,
		DEAD
	};

	State m_state = State::ALIVE;

	bool m_isActive = false;

};