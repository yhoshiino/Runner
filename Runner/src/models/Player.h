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
private:

	float m_speed = 450.f;
};