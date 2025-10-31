#pragma once
#include "UITextElement.h"
#include "../core/GameStats.h"
#include "SFML/Graphics.hpp"


class UIGameStatsText : public UITextElement
{
public:

	UIGameStatsText(GameStats* gameStats);

	void update(float deltatime) override;
	void render(sf::RenderWindow& window) override;

private:


	sf::Text m_distance;
	GameStats* m_gameStats;

};

