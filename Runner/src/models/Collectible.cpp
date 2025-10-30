#include "Collectible.h"
#include "../core/GameStats.h"

Collectible::Collectible(GameStats* gameStats, sf::Vector2f spawnPosition, char collectibleUID): 
	Entity(gameStats, spawnPosition)
{
	m_uid = collectibleUID;

	m_square.setSize({ m_COLLECTIBLE_SIZE, m_COLLECTIBLE_SIZE });
	m_square.setOutlineColor(sf::Color::Yellow);
	m_square.setOutlineThickness(2.f);
	m_square.setFillColor(sf::Color::Transparent);

	m_hitbox.size = { m_COLLECTIBLE_SIZE, m_COLLECTIBLE_SIZE };
}

Collectible::Collectible(GameStats* gameStats, char collectibleUID):
	Entity(gameStats, sf::Vector2f{0.f, 0.f})
{
	m_uid = collectibleUID;

	m_square.setSize({ m_COLLECTIBLE_SIZE, m_COLLECTIBLE_SIZE });
	m_square.setOutlineColor(sf::Color::Yellow);
	m_square.setOutlineThickness(2.f);
	m_square.setFillColor(sf::Color::Transparent);

	m_hitbox.size = { m_COLLECTIBLE_SIZE, m_COLLECTIBLE_SIZE };
}

void Collectible::onHit(Entity* otherEntity)
{
	m_isActive = false;
}
