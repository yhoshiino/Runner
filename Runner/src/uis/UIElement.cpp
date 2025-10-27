#include "UIElement.h"

UIElement::UIElement(sf::Vector2f size, sf::Vector2f position)
    : m_size(size), m_position(position)
{
}

void UIElement::setPosition(sf::Vector2f newPosition)
{
    m_position = newPosition;
}

void UIElement::setSize(sf::Vector2f newSize)
{
    m_size = newSize;
}

void UIElement::setVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

sf::Vector2f UIElement::getPosition() const
{
    return m_position;
}

sf::Vector2f UIElement::getSize() const
{
    return m_size;
}

sf::FloatRect UIElement::getBounds() const
{
    return sf::FloatRect{ m_position, m_size };
}

bool UIElement::isVisible() const
{
    return m_isVisible;
}
