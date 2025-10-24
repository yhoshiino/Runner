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
	const float TOP_LIMIT = 1080.f * 0.25f;
	const float BOTTOM_LIMIT = 1080.f * 0.75f - m_hitbox.size.y;
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

sf::Vector2f Player::getDesiredVelocity() const
{
	return m_desiredVelocity;
}
