#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class Game;

class UIManager
{
public:
    UIManager(Game* game);


    void addUIElement(std::shared_ptr<UIElement> element);
    void updateUIs(float deltaTime);
    void renderUIs(sf::RenderWindow& window);
    void handleUIEvents(const sf::Event& event, const sf::RenderWindow& window);

    void generateMainMenuUIs();
    void generateDefeatUIs();

    bool isMouseOverUI(const sf::Vector2i& worldPosition) const;

    bool isPlayButtonPressed() const;
private:

    Game* m_game = nullptr;

    std::vector<std::shared_ptr<UIElement>> m_uiElements;
    std::function<void()> m_pendingAction;

    bool m_playButtonClicked = false;
};