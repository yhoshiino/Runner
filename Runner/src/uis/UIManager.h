
#pragma once

#include "UIElement.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>


/*
 * UIManager class
 * ----------------
 * UIManager handles all User Interface (UI) elements in the game.
 * Responsibilities include:
 *   - Initializing UI elements with references to game data and stage
 *   - Updating and rendering all UI elements
 *   - Handling input events (mouse clicks, drags, etc.)
 *   - Generating different UI screens (Fish Tank, Upgrades, Equip, Battle)
 *
 * UI elements can be either:
 *   - Screen-space or
 *   - World-space (attached to the game world, e.g., UIBaseHealthInfo)
 *
 * Example usage:
 *   auto uiManager = std::make_shared<UIManager>();
 *   uiManager->init(dataLoader, stage);
 *   uiManager->generate_fish_tank_uis();
 *   uiManager->update_uis(deltaTime);
 *   uiManager->render_uis(window, uiCamera, worldCamera);
 */

class UIManager
{
public:

    UIManager() = default;

    // Initialize UIManager with game data and stage reference

    // Add a single UI element to the manager
    void add_ui_element(std::shared_ptr<UIElement> element);

    // Update all UI elements
    void update_uis(float deltaTime);

    // Render all UI elements, handling screen-space vs world-space rendering
    void render_uis(sf::RenderWindow& window, sf::View& uiView, sf::View& worldView);

    // Handle input events for all UI elements
    void handle_ui_events(const sf::Event& event, const sf::RenderWindow& window);

    // Generate specific UI layouts/screens

    void generate_victory_uis();
    void generate_defeat_uis();

    // Returns true if a given world position overlaps any UI element
    bool is_mouse_over_ui(const sf::Vector2i& worldPosition) const;

private:

    std::vector<std::shared_ptr<UIElement>> m_uiElements; // All active UI elements

    std::function<void()> m_pendingAction;              // Deferred action triggered by UI
};
