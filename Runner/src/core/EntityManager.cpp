#include "EntityManager.h"
#include "../utils/CollisionUtils.h"

#include <memory>

EntityManager::EntityManager(GameStats* gameStatsRef):
	m_gameStats(gameStatsRef),
	m_player(std::make_unique<Player>(m_gameStats, sf::Vector2f{ 700.f, 540.f }))
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

	for(auto& obstacle : m_obstacles)
	{
		obstacle->update(deltaTime);
	}

	m_player->handleInputs();
	applyPlayerMovement(deltaTime);
	m_player->update(deltaTime);

	updateColisions(deltaTime);
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
	const sf::Vector2f prevPos = m_player->getPreviousPosition();
	const sf::Vector2f currPos = m_player->getPosition();

	for (auto& obstacle : m_obstacles)
	{
		if (!obstacle) continue;

		const sf::FloatRect obstacleHitbox = obstacle->getHitbox();

		// Continuous Collision Detection (CCD)
		if (utils::lineIntersectsRect(prevPos, currPos, obstacleHitbox))
		{
			m_player->onHit(obstacle.get());
			obstacle->onHit(m_player.get());
		}
	}
}

void EntityManager::applyPlayerMovement(float deltaTime)
{
	const float conveyorSpeed = m_gameStats->getConveyorSpeed();
	const sf::Vector2f conveyorVelocity(-conveyorSpeed, 0.f);

	const sf::Vector2f desiredVelocity = m_player->getDesiredVelocity() * m_player->getSpeed();
	const sf::Vector2f totalVelocity = conveyorVelocity + desiredVelocity;

	sf::FloatRect playerHitbox = m_player->getHitbox();

	sf::FloatRect nextHitboxX = playerHitbox;
	nextHitboxX.position.x += totalVelocity.x * deltaTime;

	sf::FloatRect nextHitboxY = playerHitbox;
	nextHitboxY.position.y += totalVelocity.y * deltaTime;

	bool collidesX = false;
	bool collidesY = false;

	for (const auto& obstacle : m_obstacles)
	{
		if (!obstacle) continue;

		const sf::FloatRect& obstacleHitbox = obstacle->getHitbox();

		if (nextHitboxX.findIntersection(obstacleHitbox).has_value())
			collidesX = true;
		if (nextHitboxY.findIntersection(obstacleHitbox).has_value())
			collidesY = true;

		if (collidesX && collidesY)
			break;
	}

	sf::Vector2f finalVelocity{
		collidesX ? 0.f : totalVelocity.x,
		collidesY ? 0.f : totalVelocity.y
	};

	m_player->move(finalVelocity * deltaTime);
}

void EntityManager::spawnEntity(int entityUID, sf::Vector2f position) 
{
	// The UID will have more use in the future

	auto newEntity = std::make_unique<Entity>(m_gameStats, position);
	m_obstacles.push_back(std::move(newEntity));
}


void EntityManager::resetPlayerPosition() {
	if (m_player->isOnFire()) {
		m_player->reset();
	}
}