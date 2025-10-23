#pragma once
#include "Entity.h"


class Player : public Entity
{
public:

	Player(sf::Vector2f spawnPosition);
	~Player();

	void update(float deltatime) override;
	void draw(sf::RenderWindow& window) override;

	bool isColliding(sf::FloatRect otherHitbox) override;
	void onHit(Entity* otherEntity) override;

	void handleInputs();

	bool isOnFire();

	void reset();

private:

	float m_speed = 450.f;
};