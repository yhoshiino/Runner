#include "Entity.h"

Entity::Entity(GameStats* gameStatsRef, sf::Vector2f spawnPosition) :
	m_gameStats(gameStatsRef), m_position(spawnPosition),
	m_sprite(m_texture)
{


	m_square.setPosition(m_position);
	m_square.setSize({ m_SIZE, m_SIZE });
	m_square.setFillColor(sf::Color::Transparent);
	m_square.setOutlineColor(sf::Color::Red);
	m_square.setOutlineThickness(2.f);

	m_hitbox = sf::FloatRect(m_position, { m_SIZE, m_SIZE });

	bool textureFound = m_texture.loadFromFile("assets/textures/sprites/crate.png");
	if (textureFound)
	{
		m_sprite.setTexture(m_texture, true);
		m_sprite.setScale(sf::Vector2f{ m_SIZE / m_texture.getSize().x, m_SIZE / m_texture.getSize().y });
	}
	else
	{
		std::cerr << "Entity texture not found\n";
	}

}

Entity::Entity(GameStats* gameStatsRef): m_gameStats(gameStatsRef), m_sprite(m_texture)
{
	m_square.setPosition(m_position);
	m_square.setSize({ m_SIZE, m_SIZE });
	m_square.setFillColor(sf::Color::Transparent);
	m_square.setOutlineColor(sf::Color::Red);
	m_square.setOutlineThickness(2.f);

	m_hitbox = sf::FloatRect(m_position, { m_SIZE, m_SIZE });

	bool textureFound = m_texture.loadFromFile("assets/textures/sprites/crate.png");
	if (textureFound)
	{
		m_sprite.setTexture(m_texture, true);
		m_sprite.setScale(sf::Vector2f{ m_SIZE / m_texture.getSize().x, m_SIZE / m_texture.getSize().y });
	}
	else
	{
		std::cerr << "Entity texture not found\n";
	}
}

Entity::~Entity()
{
}

void Entity::update(float deltaTime)
{
	if (m_position.x <= 1900.f && m_wasActivated == false) 
	{
		m_isActive = true; 
		m_wasActivated = true;
	}

	m_velocity.x -= m_gameStats->getConveyorSpeed(); // Moves on the left
	m_previousPosition = m_position;
	m_position += m_velocity * deltaTime;

	m_hitbox.position = m_position;
	m_square.setPosition(m_position);
	m_sprite.setPosition(m_position);

	m_velocity = { 0.f, 0.f };
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

bool Entity::isColliding(sf::FloatRect otherHitbox, float deltaTime)
{
	// Predict next position based on velocity
	sf::FloatRect nextHitbox = m_hitbox;
	nextHitbox.position += m_velocity;

	return nextHitbox.findIntersection(otherHitbox).has_value();
}

void Entity::onHit(Entity* otherEntity)
{
}

void Entity::addVelocity(sf::Vector2f newVelocity)
{
	m_velocity += newVelocity;
}

sf::Vector2f Entity::getPosition() const
{
	return m_position;
}

sf::Vector2f Entity::getPreviousPosition() const
{
	return m_previousPosition;
}

sf::FloatRect Entity::getHitbox() const
{
	return m_hitbox;
}

bool Entity::isActive() const
{
	return m_isActive;
}

void Entity::setPosition(sf::Vector2f newPos) {
	m_position = newPos;
}

float Entity::getConveyorSpeed() const
{
	return m_gameStats->getConveyorSpeed();
}

