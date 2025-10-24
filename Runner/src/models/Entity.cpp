#include "Entity.h"

Entity::Entity(sf::Vector2f spawnPosition) :
	m_position(spawnPosition)
{
	m_square.setPosition(m_position);
	m_square.setSize({ m_SIZE, m_SIZE });
	m_square.setFillColor(sf::Color::Transparent);
	m_square.setOutlineColor(sf::Color::Red);
	m_square.setOutlineThickness(2.f);

	m_hitbox = sf::FloatRect(m_position, { m_SIZE, m_SIZE });
}

Entity::Entity()
{
	m_square.setPosition(m_position);
	m_square.setSize({ m_SIZE, m_SIZE });
	m_square.setFillColor(sf::Color::Transparent);
	m_square.setOutlineColor(sf::Color::Red);
	m_square.setOutlineThickness(2.f);

	m_hitbox = sf::FloatRect(m_position, { m_SIZE, m_SIZE });
}

Entity::~Entity()
{
}

void Entity::update(float deltaTime)
{
	m_velocity.x -= 200.f; // Moves on the left
	m_position += m_velocity * deltaTime;

	m_hitbox.position = m_position;
	m_square.setPosition(m_position);

	m_velocity = { 0.f, 0.f };
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(m_square);
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

sf::FloatRect Entity::getHitbox() const
{
	return m_hitbox;
}

void Entity::setPosition(sf::Vector2f newPos) {
	m_position = newPos;
}
