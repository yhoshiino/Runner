#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity 
{
public:

	Entity(sf::Vector2f spawnPosition);
	Entity() = default;

	virtual ~Entity();

	virtual void update(float deltatime);
	virtual void draw(sf::RenderWindow& window);

	virtual bool isColliding(sf::FloatRect otherHitbox);
	virtual void onHit(Entity * otherEntity);

protected:
	sf::Vector2f m_position = { 0.f, 0.f };
	sf::Vector2f m_velocity = { 0.f, 0.f };
	sf::FloatRect m_hitbox;

	sf::RectangleShape m_square;

	const float m_SIZE = 72.f;
private:

	int m_health = 5;
	

	

	enum class State 
	{
		ALIVE,
		DEAD
	};

	State m_state = State::ALIVE;

	bool m_isActive = false;


};