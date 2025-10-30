#include "Player.h"


Player::Player(GameStats* gameStatsRef, sf::Vector2f spawnPosition) :
	Entity::Entity(gameStatsRef, spawnPosition)
{
	m_square.setSize({ m_PLAYER_SIZE, m_PLAYER_SIZE });
	m_square.setOutlineColor(sf::Color::Green);
	m_square.setOutlineThickness(2.f);
	m_square.setFillColor(sf::Color::Transparent);

	m_hitbox.size = { m_PLAYER_SIZE, m_PLAYER_SIZE };
}


Player::~Player()
{

}

void Player::update(float deltaTime)
{
	isOnFire();

	// Normalize movement velocity
	if (m_velocity.x != 0.f || m_velocity.y != 0.f)
	{
		float len = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
		m_velocity /= len;
	}

	m_speed = m_gameStats->getConveyorSpeed() * m_CONVEYOR_SPEED_FACTOR;

	m_velocity = { 0.f, 0.f };
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_square);
}

void Player::move(const sf::Vector2f& movementVector)
{
	m_previousPosition = m_position;

	m_position += movementVector;

	m_hitbox.position = m_position;
	m_square.setPosition(m_position);
}

// Called when player collides with another entity (currently empty)
void Player::onHit(Entity* otherEntity)
{
	//m_velocity.x -= 300.f; //Temporary pushback
}

void Player::handleInputs()
{
	m_desiredVelocity = { 0.f, 0.f };

	// Check for inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		m_desiredVelocity.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		m_desiredVelocity.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		m_desiredVelocity.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		m_desiredVelocity.y += 1.f;

	// Apply clamping
	const float TOP_LIMIT = 288;
	const float BOTTOM_LIMIT = 792 - m_hitbox.size.y;
	if (m_position.y <= TOP_LIMIT && m_desiredVelocity.y < 0.f)
		m_desiredVelocity.y = 0.f;

	if (m_position.y >= BOTTOM_LIMIT && m_desiredVelocity.y > 0.f)
		m_desiredVelocity.y = 0.f;

	// Normalize desired velocity
	const float length = std::sqrt(
		(m_desiredVelocity.x * m_desiredVelocity.x) +
		(m_desiredVelocity.y * m_desiredVelocity.y)
	);

	if (length > 0.f) m_desiredVelocity /= length;
}

bool Player::isOnFire()
{
	if (m_position.x <= 269.f)
	{
		return true;
	}
	return false;
}

void Player::reset() {
	m_position = { 700.f, 540.f };
	m_previousPosition = m_position;
}

sf::Vector2f Player::getDesiredVelocity() const
{
	return m_desiredVelocity;
}

float Player::getSpeed() const
{
	return m_speed;
}

float Player::getConveyorSpeedFactor() const
{
	return m_CONVEYOR_SPEED_FACTOR;
}
