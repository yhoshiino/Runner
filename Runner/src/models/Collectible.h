#pragma once

#include "Entity.h"

class GameStats;

class Collectible : public Entity
{
public:
	Collectible(GameStats* gameStats, sf::Vector2f spawnPosition, char collectibleUID);
	Collectible(GameStats* gameStats, char collectibleUID);

	void onHit(Entity* otherEntity) override;

private:

	const float m_COLLECTIBLE_SIZE = 20.f;
	char m_uid = 'a';
};