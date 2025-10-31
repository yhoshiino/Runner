#include "UIGameStatsText.h"

UIGameStatsText::UIGameStatsText(GameStats* gameStats) : UITextElement(sf::Vector2f(200.f, 100.f), sf::Vector2f(0.f, 0.f)), m_gameStats(gameStats), m_distance(m_font)
{
	m_distance.setPosition(sf::Vector2f(0.f, 100.f));
	m_distance.setCharacterSize(50);
	m_distance.setOutlineColor(sf::Color::Black);
	m_distance.setOutlineThickness(1.5f);
}

void UIGameStatsText::update(float deltatime)
{
	m_text.setString("Score : " + std::to_string((int)m_gameStats->getScore()));
	m_text.setCharacterSize(50);
	m_distance.setString("Distance : " + std::to_string((int)m_gameStats->getDistance()));

}

void UIGameStatsText::render(sf::RenderWindow& window)
{
	window.draw(m_distance);
	window.draw(m_text);
}

