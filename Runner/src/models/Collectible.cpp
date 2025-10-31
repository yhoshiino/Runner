#include "Collectible.h"
#include "Player.h"
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

	bool textureFound = m_texture.loadFromFile("assets/textures/sprites/Bolt.png");
	if (textureFound)
	{
		m_sprite.setTexture(m_texture, true);
		m_sprite.setScale(sf::Vector2f{ m_COLLECTIBLE_SIZE / m_texture.getSize().x, m_COLLECTIBLE_SIZE / m_texture.getSize().y });
	}
	else
	{
		std::cerr << "Collectible texture not found\n";
	}
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

	bool textureFound = m_texture.loadFromFile("assets/textures/sprites/Bolt.png");
	if (textureFound)
	{
		m_sprite.setTexture(m_texture, true);
		m_sprite.setScale(sf::Vector2f{ m_COLLECTIBLE_SIZE / m_texture.getSize().x, m_COLLECTIBLE_SIZE / m_texture.getSize().y });
	}
	else
	{
		std::cerr << "Collectible texture not found\n";
	}
}

void Collectible::onHit(Entity* otherEntity)
{
	if (!dynamic_cast<Player*>(otherEntity)) return; // Only triggers when the player touches it

	m_gameStats->addScore(5);
	m_isActive = false;
}
