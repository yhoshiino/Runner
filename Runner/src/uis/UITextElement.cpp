#include "UITextElement.h"

UITextElement::UITextElement(sf::Vector2f size, sf::Vector2f position)
    : m_text(m_font, "Text", 30)
{
    m_font.openFromFile("assets/fonts/robotaur.ttf");
    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);
}

UITextElement::UITextElement(sf::Vector2f size, sf::Vector2f position, const std::string& text)
    : m_text(m_font, text, 30)
{
    m_font.openFromFile("assets/fonts/robotaur.ttf");
    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);
}

UITextElement::UITextElement(sf::Vector2f size, sf::Vector2f position, const std::string& text, float characterSize)
    : m_text(m_font, text, characterSize)
{
    m_font.openFromFile("assets/fonts/robotaur.ttf");
    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);
}

void UITextElement::setText(const std::string& text)
{
    m_text.setString(text);
}

void UITextElement::setTextColor(const sf::Color& color)
{
    m_text.setFillColor(color);
    if (color.a == 0) m_text.setOutlineColor(sf::Color(0, 0, 0, 0));
}

void UITextElement::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
}

void UITextElement::update(float deltaTime)
{
    m_text.setPosition(m_position);
}

void UITextElement::render(sf::RenderWindow& window)
{
    if (m_isVisible)
        window.draw(m_text);
}

sf::Text& UITextElement::getText()
{
    return m_text;
}
