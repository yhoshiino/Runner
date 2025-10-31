#include "UIFinalScoreTextElement.h"

UIFinalScoreTextElement::UIFinalScoreTextElement(GameStats* gameStats) : UITextElement(sf::Vector2f(200.f, 100.f), sf::Vector2f(1920/0.3f, 500.f)), m_gameStats(gameStats)
{
}

void UIFinalScoreTextElement::update(float deltatime)
{
	m_text.setString("Score : " + std::to_string((int)m_gameStats->getScore()));
	m_text.setCharacterSize(70);
}

void UIFinalScoreTextElement::render(sf::RenderWindow& window)
{
	window.draw(m_text);
}
