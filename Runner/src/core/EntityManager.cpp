#include "EntityManager.h"
#include <memory>

EntityManager::EntityManager(): 
	m_player(std::make_unique<Player>(sf::Vector2f{ 200.f, 580.f }))
{
	
}

EntityManager::~EntityManager()
{
}

void EntityManager::updateAll(float deltaTime)
{
	// Remove obstacles that are out of the screen
	std::erase_if(m_obstacles, [](const std::unique_ptr<Entity>& obstacle)
		{
			//std::cout << "Removed obstacle at x: " << obstacle->getPosition().x << std::endl;
			return obstacle->getPosition().x <= -75.0f;
		});

	//std::cout << "Obstacles count: " << m_obstacles.size() << std::endl;

	updateColisions(deltaTime);

	for(auto& obstacle : m_obstacles)
	{
		obstacle->update(deltaTime);
	}

	m_player->handleInputs(m_obstacles);
	applyPlayerMovement();
	m_player->update(deltaTime);
}

void EntityManager::drawAll(sf::RenderWindow& window) 
{
	for (auto& obstacle : m_obstacles)
	{
		obstacle->draw(window);
	}

	m_player->draw(window);
}

void EntityManager::updateColisions(float deltaTime) 
{
	if (!m_player) return;

	const sf::FloatRect playerHitbox = m_player->getHitbox();

	for (auto& obstacle : m_obstacles)
	{
		if (!obstacle) continue;

		const sf::FloatRect obstacleHitbox = obstacle->getHitbox();

		// Check collision
		if (m_player->isColliding(obstacleHitbox, deltaTime))
		{

			//std::cout << "Collision detected between player and obstacle!" << std::endl;

			// Notify both entities
			m_player->onHit(obstacle.get());
			obstacle->onHit(m_player.get());
		}
	}
}

void EntityManager::applyPlayerMovement()
{
	const sf::Vector2f desiredVelocity = m_player->getDesiredVelocity();
	const sf::FloatRect playerHitbox = m_player->getHitbox();

	sf::FloatRect nextHitboxX = playerHitbox;
	nextHitboxX.position.x += desiredVelocity.x;

	sf::FloatRect nextHitboxY = playerHitbox;
	nextHitboxY.position.y += desiredVelocity.y;

	bool collidesX = false;
	bool collidesY = false;

	for (const auto& obstacle : m_obstacles)
	{
		if (!obstacle)
			continue;

		const sf::FloatRect& obstacleHitbox = obstacle->getHitbox();

		if (nextHitboxX.findIntersection(obstacleHitbox).has_value())
			collidesX = true;

		if (nextHitboxY.findIntersection(obstacleHitbox).has_value())
			collidesY = true;

		if (collidesX && collidesY)
			break;
	}

	sf::Vector2f movementVelocity
	{
		collidesX ? 0.f : desiredVelocity.x,
		collidesY ? 0.f : desiredVelocity.y,
	};

	m_player->addVelocity(movementVelocity);
}

void EntityManager::spawnEntity(int entityUID, sf::Vector2f position) 
{
	// The UID will have more use in the future

	auto newEntity = std::make_unique<Entity>(position);
	m_obstacles.push_back(std::move(newEntity));
}
