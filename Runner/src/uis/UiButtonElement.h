#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

/*
 * UIButtonElement
 * ----------------
 * Clickable button with text, callback, and shape
 */

class UIButtonElement : public UIElement
{
public:

    UIButtonElement(sf::Vector2f size, sf::Vector2f position);
    UIButtonElement(sf::Vector2f size, sf::Vector2f position, const std::string& text);

    void setCallback(std::function<void()> callback);
    void centerText();

    void setText(const std::string& text);
    void setTextSize(unsigned int size);
    void setTextColor(const sf::Color& color);

    void setFillColor(const sf::Color& color);
    void setOutline(float thickness, const sf::Color& color);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

protected:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Font m_font;
    std::function<void()> m_callback;
};
