#pragma once
#include "UITextElement.h"
#include "../core/GameStats.h"
#include "SFML/Graphics.hpp"

class UIFinalScoreTextElement :
    public UITextElement
{
public:

    UIFinalScoreTextElement(GameStats* gameStats);

    void update(float deltatime) override;
    void render(sf::RenderWindow& window) override;

private:

    GameStats* m_gameStats;

};

