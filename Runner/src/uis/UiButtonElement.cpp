#include "UIButtonElement.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

UIButtonElement::UIButtonElement(sf::Vector2f size, sf::Vector2f position)
    : m_shape(size), m_text(m_font, "Button", 30)
{
    m_font.openFromFile("assets/fonts/robotaur.ttf");

    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);

    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color(255, 225, 145));

    centerText();
}

UIButtonElement::UIButtonElement(sf::Vector2f size, sf::Vector2f position, const std::string& text)
    : m_shape(size), m_text(m_font, text, 30)
{
    m_font.openFromFile("assets/fonts/robotaur.ttf");

    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);

    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color(255, 225, 145));

    centerText();
}

void UIButtonElement::setCallback(std::function<void()> callback)
{
    m_callback = callback;
}

void UIButtonElement::centerText()
{
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
        });
    m_text.setPosition({
        m_shape.getPosition().x + m_shape.getSize().x / 2.f,
        m_shape.getPosition().y + m_shape.getSize().y / 2.f
        });
}

void UIButtonElement::setText(const std::string& text)
{
    m_text.setString(text);
}

void UIButtonElement::setTextSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}

void UIButtonElement::setTextColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

void UIButtonElement::setFillColor(const sf::Color& color)
{
    m_shape.setFillColor(color);
}

void UIButtonElement::setOutline(float thickness, const sf::Color& color)
{
    m_shape.setOutlineThickness(thickness);
    m_shape.setOutlineColor(color);
}

void UIButtonElement::update(float deltaTime)
{
    centerText();
}

void UIButtonElement::render(sf::RenderWindow& window)
{
    if (m_isVisible)
    {
        window.draw(m_shape);
        window.draw(m_text);
    }
}

void UIButtonElement::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePressed->position);
            if (m_shape.getGlobalBounds().contains(worldPos))
            {
                if (m_callback) m_callback();
            }
        }
    }
}

sf::FloatRect UIButtonElement::getBounds() const
{
    return m_shape.getGlobalBounds();
}
