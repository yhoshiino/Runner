#pragma once
#include "Entity.h"


class Player : public Entity
{
public:

	Player(sf::Vector2f spawnPosition);
	~Player();

	void update(float deltatime) override;
	void draw(sf::RenderWindow& window) override;

	void onHit(Entity* otherEntity) override;

	void handleInputs(const std::vector<std::unique_ptr<Entity>>& obstacles);

	sf::Vector2f getDesiredVelocity() const;

private:

	float m_speed = 450.f;
	sf::Vector2f m_desiredVelocity = { 0.f, 0.f }; // Velocity used for movement input
};