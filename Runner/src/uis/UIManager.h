#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class UIManager
{
public:
    UIManager() = default;

    void addUIElement(std::shared_ptr<UIElement> element);
    void updateUIs(float deltaTime);
    void renderUIs(sf::RenderWindow& window, sf::View& uiView, sf::View& worldView);
    void handleUIEvents(const sf::Event& event, const sf::RenderWindow& window);

    void generateMainMenuUIs();
    void generateVictoryUIs();
    void generateDefeatUIs();

    bool isMouseOverUI(const sf::Vector2i& worldPosition) const;

private:
    std::vector<std::shared_ptr<UIElement>> m_uiElements;
    std::function<void()> m_pendingAction;
};