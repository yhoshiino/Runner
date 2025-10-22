#include "Entity.h"

Entity::Entity(math::Vector2<float> spawnPosition, math::Vector2<float> initialVelocity) :
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
