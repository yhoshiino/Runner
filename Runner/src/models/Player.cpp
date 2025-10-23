#include "Player.h"


Player::Player(sf::Vector2f spawnPosition) :
	Entity::Entity(spawnPosition)
{
	m_square.setSize({ m_SIZE, m_SIZE });
	m_square.setOutlineColor(sf::Color::Green);
	m_square.setOutlineThickness(2.f);
	m_square.setFillColor(sf::Color::Transparent);
}


Player::~Player()
{

}

void Player::update(float deltatime)
{
	sf::Vector2f autoMove(-50.f, 0.f); // automatic movement vector

	// Normalize manual movement velocity
	if (m_velocity.x != 0.f || m_velocity.y != 0.f)
	{
		float len = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
		m_velocity /= len;
	}

	float manualSpeed = 200.f; // manual movement speed
	handleInputs();             // read keyboard input
	m_position += autoMove * deltatime;                  // apply automatic movement
	m_position += m_velocity * manualSpeed * deltatime; // apply manual movement
	m_square.setPosition(m_position);                   // update square position
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_square);
}

// Collision detection placeholder (currently always false)
bool Player::isColliding(sf::FloatRect otherHitbox)
{
	return false;
}

// Called when player collides with another entity (currently empty)
void Player::onHit(Entity* otherEntity)
{

}

void Player::handleInputs()
{
	m_velocity = { 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		if (m_position.x > 0) {
			m_velocity.x += -1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (m_position.x < 1920 - m_SIZE) {
			m_velocity.x += 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		if (m_position.y > 1080 * 0.25f) {
			m_velocity.y += -1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (m_position.y < 1080 * 0.75f) {
			m_velocity.y += 1;
		}
	}
}
