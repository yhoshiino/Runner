#include "Entity.h"

Entity::Entity(sf::Vector2f spawnPosition, sf::Vector2f initialVelocity) :
	m_position(spawnPosition),
	m_velocity(initialVelocity)
{
}

Entity::~Entity()
{
}

void Entity::update(float deltatime)
{
}

void Entity::draw(sf::RenderWindow& window)
{
}

bool Entity::isColliding(sf::FloatRect otherHitbox)
{
	return false;
}

void Entity::onHit(Entity* otherEntity)
{
}
