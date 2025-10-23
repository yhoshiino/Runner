#include "Entity.h"

Entity::Entity(sf::Vector2f spawnPosition) :
	m_position(spawnPosition)
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
