#pragma once

#include <SFML/Graphics.hpp>

/*
 * Base class for all UI elements
 */

class UIElement
{
public:

    UIElement() = default;
    UIElement(sf::Vector2f size, sf::Vector2f position);
    virtual ~UIElement() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {}

    // Setters
    virtual void setPosition(sf::Vector2f newPosition);
    virtual void setSize(sf::Vector2f newSize);
    virtual void setVisible(bool isVisible);

    // Getters
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    virtual sf::FloatRect getBounds() const;
    bool isVisible() const;

public:
    bool isWorldSpaceUi = false;

protected:
    sf::Vector2f m_position = { 0.f, 0.f };
    sf::Vector2f m_size = { 0.f, 0.f };
    bool m_isVisible = true;
};
