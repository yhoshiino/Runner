#pragma once
#include "Entity.h"

class Player : public Entity
{
public:

	Player(GameStats* gameStats, sf::Vector2f spawnPosition);
	~Player();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void move(const sf::Vector2f& movementVector);
	void onHit(Entity* otherEntity) override;

	void handleInputs();

	bool isOnFire();

	void resetPlayer();

	sf::Vector2f getDesiredVelocity() const;
	float getConveyorSpeedFactor() const;
	float getSpeed() const;

private:

	float m_speed = 100.f;
	const float m_CONVEYOR_SPEED_FACTOR = 1.75f; // How much faster is the player compared to the conveyor speed

	sf::Vector2f m_desiredVelocity = { 0.f, 0.f }; // Velocity used for movement input
};