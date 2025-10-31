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
	std::erase_if(m_gameObjects, [](const std::unique_ptr<Entity>& obstacle)
		{
			//std::cout << "Removed obstacle at x: " << obstacle->getPosition().x << std::endl;
			return obstacle->getPosition().x <= -75.0f;
		});

	//std::cout << "Obstacles count: " << m_obstacles.size() << std::endl;

	for(auto& gameObject : m_gameObjects)
	{
		gameObject->update(deltaTime);
	}

	m_player->handleInputs();
	applyPlayerMovement(deltaTime);
	m_player->update(deltaTime);

	updateColisions(deltaTime);
}

void EntityManager::drawAll(sf::RenderWindow& window) 
{
	for (auto& gameObject : m_gameObjects)
	{
		if (!gameObject) continue;
		if (!gameObject->isActive()) continue;

		gameObject->draw(window);
	}

	m_player->draw(window);
}

void EntityManager::updateColisions(float deltaTime)
{
	if (!m_player) return;

	const sf::Vector2f PREVIOUS_POS = m_player->getPreviousPosition();
	const sf::Vector2f CURRENT_POS = m_player->getPosition();

	const sf::FloatRect PLAYER_HITBOX = m_player->getHitbox();
	const sf::Vector2f PLAYER_HALF_SIZE = PLAYER_HITBOX.size * 0.5f;

	const sf::Vector2f PLAYER_START_CENTER = PREVIOUS_POS + PLAYER_HALF_SIZE;
	const sf::Vector2f PLAYER_END_CENTER = CURRENT_POS + PLAYER_HALF_SIZE;

	for (auto& gameObject : m_gameObjects)
	{
		if (!gameObject) continue;
		if (!gameObject->isActive()) continue;

		const sf::FloatRect OBJECT_HITBOX = gameObject->getHitbox();

		/*
		* Continuous Collision Detection (CCD):
		* We trace the player's center across its movement
		* and check if the segment intersects the object's hitbox.
		*/
		bool intersects = utils::lineIntersectsRect(PLAYER_START_CENTER, PLAYER_END_CENTER, OBJECT_HITBOX);

		// We check for AABB overlap here (Axis Aligned Bounding Box)
		if (!intersects)
		{
			const bool OVERLAP_X =
				PLAYER_HITBOX.position.x + PLAYER_HITBOX.size.x >= OBJECT_HITBOX.position.x &&
				OBJECT_HITBOX.position.x + OBJECT_HITBOX.size.x >= PLAYER_HITBOX.position.x;

			const bool OVERLAP_Y =
				PLAYER_HITBOX.position.y + PLAYER_HITBOX.size.y >= OBJECT_HITBOX.position.y &&
				OBJECT_HITBOX.position.y + OBJECT_HITBOX.size.y >= PLAYER_HITBOX.position.y;

			if (OVERLAP_X && OVERLAP_Y)
				intersects = true;
		}

		if (intersects)
		{
			m_player->onHit(gameObject.get());
			gameObject->onHit(m_player.get());
		}
	}
}

void EntityManager::applyPlayerMovement(float deltaTime)
{
	const float CONVEYOR_SPEED = m_gameStats->getConveyorSpeed();
	const sf::Vector2f CONVEYOR_VELOCITY{-CONVEYOR_SPEED, 0.f};

	const float LEFT_X_COLLISION_OFFSET = 1.f; // In pxs
	const float EPSILON = 0.0001f;

	const sf::Vector2f DESIRED_POSITION = m_player->getDesiredVelocity() * m_player->getSpeed();
	const sf::Vector2f TOTAL_VELOCITY = CONVEYOR_VELOCITY + DESIRED_POSITION;

	sf::FloatRect playerHitbox = m_player->getHitbox();

	sf::FloatRect nextHitboxX = playerHitbox;
	nextHitboxX.position.x += TOTAL_VELOCITY.x * deltaTime;

	sf::FloatRect nextHitboxY = playerHitbox;
	nextHitboxY.position.y += TOTAL_VELOCITY.y * deltaTime;

	bool collidesX = false;
	bool collidesY = false;
	bool collideFromLeft = false;

	for (const auto& gameObject : m_gameObjects)
	{
		if (!gameObject) continue;
		if (dynamic_cast<Collectible*>(gameObject.get())) continue; // Do not stop the player when they hit a collectible

		const sf::FloatRect& OBJECT_HITBOX = gameObject->getHitbox();

		if (nextHitboxX.findIntersection(OBJECT_HITBOX).has_value())
		{
			collidesX = true;

			// Determine if collision happens from the left or right
			const float PLAYER_CENTER_X = playerHitbox.position.x + playerHitbox.size.x * 0.5f;
			const float OBJECT_CENTER_X = OBJECT_HITBOX.position.x + OBJECT_HITBOX.size.x * 0.5f;

			// If centers are different enough use that. Otherwise fall back to velocity sign.
			if (std::abs(PLAYER_CENTER_X - OBJECT_CENTER_X) > EPSILON)
			{
				collideFromLeft = (PLAYER_CENTER_X < OBJECT_CENTER_X);
			}
			else
			{
				// Exact edge case: use movement direction to decide
				if (TOTAL_VELOCITY.x > 0.f) collideFromLeft = true;
				else if (TOTAL_VELOCITY.x < 0.f) collideFromLeft = false; // if TOTAL_VELOCITY.x == 0, leave previous value (default false)
			}
		}
		if (nextHitboxY.findIntersection(OBJECT_HITBOX).has_value())
			collidesY = true;

		if (collidesX && collidesY)
			break;
	}

	sf::Vector2f finalVelocity{
		collidesX ? CONVEYOR_VELOCITY.x : TOTAL_VELOCITY.x,
		collidesY ? CONVEYOR_VELOCITY.y : TOTAL_VELOCITY.y
	};

	sf::Vector2f moveVector = finalVelocity * deltaTime;

	if (collidesX && collideFromLeft)
		moveVector.x -= LEFT_X_COLLISION_OFFSET;

	m_player->move(moveVector);

	//std::cout << "[Final Move Vector]: " << moveVector.x << ", " << moveVector.y << std::endl;
}

void EntityManager::spawnEntity(sf::Vector2f position) 
{
	auto newEntity = std::make_unique<Entity>(m_gameStats, position);
	m_gameObjects.push_back(std::move(newEntity));
}

void EntityManager::spawnCollectible(sf::Vector2f position, char uid)
{
	auto newCollectible = std::make_unique<Collectible>(m_gameStats, position, uid);
	m_gameObjects.push_back(std::move(newCollectible));
}

void EntityManager::spawnEntity(std::unique_ptr<Entity> entityPtr)
{
	m_gameObjects.push_back(std::move(entityPtr));
}

void EntityManager::spawnEntitiesRandomly(int entitiesToSpawn, float deltaTime)
{
	static const float SPAWN_DISTANCE = 200.f;
	static float spawnAccumulator = 0.f;

	spawnAccumulator += m_gameStats->getConveyorSpeed() * deltaTime;
	if (spawnAccumulator >= SPAWN_DISTANCE)
	{
		spawnAccumulator = 0.f;
		
		for (int i = 0; i < entitiesToSpawn; ++i)
		{
			float y = 288.f + static_cast<float>(rand() % (720 - 288 + 1));
			spawnEntity({ 2000.f, y });
			spawnCollectible(sf::Vector2f{ 2000.f - 100, y }, 't');
		}
	}
}

void EntityManager::resetPlayerPosition() 
{
	if (m_player->isOnFire()) 
		m_player->reset();
}

void EntityManager::clearGameObjects()
{
	m_gameObjects.clear();
}

bool EntityManager::playerOnFire() 
{
	return m_player->isOnFire();
}