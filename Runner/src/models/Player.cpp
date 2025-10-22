#include "Player.h"


Player::Player(sf::Vector2f spawnPosition, sf::Vector2f initialVelocity)
{

}

Player::~Player()
{

}

void Player::update(float deltatime)
{
	sf::Vector2f autoMove(0.f, 50.f);

	// normalisation du mouvement manuel
	if (m_velocity.x != 0.f || m_velocity.y != 0.f)
	{
		float len = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
		m_velocity /= len;
	}

	float manualSpeed = 200.f; // vitesse contrôlée
	m_position += (m_velocity * manualSpeed + autoMove) * deltatime;
}

void Player::draw(sf::RenderWindow& window)
{
	/*window.draw(sprite);*/
}

bool Player::isColliding(sf::FloatRect otherHitbox)
{
	return false;
}

void Player::onHit(Entity* otherEntity)
{

}

void Player::handleInputs()
{
	m_velocity = {0.f, 0.f};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		m_velocity.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_velocity.x = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		m_velocity.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		m_velocity.y = 1;
	}
}
