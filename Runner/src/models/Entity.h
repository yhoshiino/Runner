#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity 
{
public:

	Entity(sf::Vector2f spawnPosition);
	Entity();

	virtual ~Entity();

	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);

	virtual bool isColliding(sf::FloatRect otherHitbox, float deltaTime);
	virtual void onHit(Entity * otherEntity);

	void addVelocity(sf::Vector2f newVelocity);

	sf::Vector2f getPosition() const;
	sf::FloatRect getHitbox() const;

protected:
	sf::Vector2f m_position = { 0.f, 0.f };
	sf::Vector2f m_velocity = { 0.f, 0.f };
	sf::FloatRect m_hitbox;

	sf::RectangleShape m_square; // For debugging

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