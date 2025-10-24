#include "Player.h"


Player::Player(sf::Vector2f spawnPosition) :
	Entity::Entity(spawnPosition)
{
	m_square.setSize({ 62.f, 62.f });
	m_square.setOutlineColor(sf::Color::Green);
	m_square.setOutlineThickness(2.f);
	m_square.setFillColor(sf::Color::Transparent);

	m_hitbox.size = { 62.f, 62.f };
}


Player::~Player()
{

}

void Player::update(float deltatime)
{
	sf::Vector2f autoMove(-200.f, 0.f); // automatic movement vector

	// Normalize manual movement velocity
	if (m_velocity.x != 0.f || m_velocity.y != 0.f)
	{
		float len = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
		m_velocity /= len;
	}

	m_position += autoMove * deltatime;                  // apply automatic movement
	m_position += m_velocity * m_speed * deltatime;		// apply speed movement
	m_square.setPosition(m_position);                   // update square position
	m_hitbox.position = m_position;                     // update hitbox position

	m_velocity = { 0.f, 0.f }; // reset velocity for next frame
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_square);
}

// Called when player collides with another entity (currently empty)
void Player::onHit(Entity* otherEntity)
{
	m_velocity.x -= 300.f; //Temporary pushback
}

void Player::handleInputs(const std::vector<std::unique_ptr<Entity>>& obstacles)
{
	sf::Vector2f desiredVelocity = { 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		desiredVelocity.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		desiredVelocity.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		desiredVelocity.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		desiredVelocity.y += 1.f;

	sf::FloatRect nextHitboxX = m_hitbox;
	nextHitboxX.position.x += desiredVelocity.x;

	sf::FloatRect nextHitboxY = m_hitbox;
	nextHitboxY.position.y += desiredVelocity.y;

	bool collidesX = false;
	bool collidesY = false;

	for (const auto& obstacle : obstacles)
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

	m_velocity.x = collidesX ? 0.f : desiredVelocity.x;
	m_velocity.y = collidesY ? 0.f : desiredVelocity.y;
}
