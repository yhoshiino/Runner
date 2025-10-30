#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <string>

/*
 * UITextElement
 * -------------
 * UI element that displays text
 */

class UITextElement : public UIElement
{
public:

    UITextElement(sf::Vector2f size, sf::Vector2f position);
    UITextElement(sf::Vector2f size, sf::Vector2f position, const std::string& text);
    UITextElement(sf::Vector2f size, sf::Vector2f position, const std::string& text, float characterSize);

    void setText(const std::string& text);
    void setTextColor(const sf::Color& color);
    void setCharacterSize(unsigned int size);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    sf::Text& getText();

protected:
    sf::Text m_text;
    sf::Font m_font;
};
