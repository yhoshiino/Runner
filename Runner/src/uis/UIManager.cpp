#include "UIManager.h"
#include "UIButtonElement.h"
#include "UITextElement.h"
#include "UITextureElement.h"

#include <iostream>


// Add a UI element to the manager
void UIManager::addUIElement(std::shared_ptr<UIElement> element)
{
    m_uiElements.push_back(element);
}

// Update all UI elements (called each frame)
void UIManager::updateUIs(float deltaTime)
{
    for (auto& element : m_uiElements)
    {
        element->update(deltaTime);
    }
}

// Render all UI elements
// Handles world-space vs screen-space rendering by switching the view as needed
void UIManager::renderUIs(sf::RenderWindow& window)
{
    for (auto& element : m_uiElements)
    {
        if (element->isWorldSpaceUi)
        {

            element->render(window);

        }
        else
        {
            element->render(window);
        }
    }
}

// Handle input events for all UI elements
void UIManager::handleUIEvents(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& uiElement : m_uiElements)
    {
        uiElement->handleEvent(event, window);
    }

    if (m_pendingAction)
    {
        auto action = m_pendingAction;
        m_pendingAction = nullptr;
        action();
    }
}


bool UIManager::isPlayButtonPressed() const
{
    // Retourne true si le bouton "Play" vient d'être cliqué
    // (selon ton implémentation UI)
    return m_playButtonClicked;
}


void UIManager::generateMainMenuUIs() {

    m_uiElements.clear();

    auto bg = std::make_shared<UITextureElement>(
        sf::Vector2f{ 1920.f, 1080.f },
        sf::Vector2f{0.f,0.f},
        "assets/textures/background/runnerBG.png"
    );

    auto title = std::make_shared<UITextElement>(
        sf::Vector2f{0.f,0.f},
        sf::Vector2f{1920 * 1/3, 100.f},
        "Robot Run",
        100
    );

    auto playButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 1920 * 0.4f + 120, 500.f },
        "PLAY"
    );
    playButton->setCallback([this]
    {
            m_pendingAction = [this]() {
                std::cout << "play!!!" << std::endl;
                };
    });

    /*auto settingsButton = std::make_shared<UIButtonElement>(

    )*/

    auto leaveButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{200.f,100.f},
        sf::Vector2f{ 1920 * 0.4f + 120, 800.f },
        "QUIT"
    );
    leaveButton->setCallback([this] 
    {
            m_pendingAction = [this]() {
                std::cout << "Quit!!!" << std::endl;
                };

            
    });

    addUIElement(bg);
    addUIElement(title);
    addUIElement(playButton);
    /*addUIElement(settingsButton);*/
    addUIElement(leaveButton);

}


// Generate victory UI layout
void UIManager::generateVictoryUIs()
{
    m_uiElements.clear();

    auto title = std::make_shared<UITextElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 0.f, 0.f },
        "Victory!",
        72
    );

    sf::FloatRect textBounds = title->getText().getLocalBounds();
    title->getText().setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
        });
    title->setPosition({ 1920.f / 2.f, 1080.f / 2.f });



    auto menuButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 20.f, 1080.f - 100.f - 20.f },
        "MENU"
    );
    menuButton->setCallback([this]() {
        /* deferred action example */
        });

    auto mapButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 150.f, 1080.f - 100.f - 20.f },
        "MAP"
    );
    mapButton->setCallback([this]() {
        /* deferred action example */
        });

    addUIElement(title);
    addUIElement(menuButton);
    addUIElement(mapButton);
}

// Generate defeat UI layout
void UIManager::generateDefeatUIs()
{
    m_uiElements.clear();

    auto title = std::make_shared<UITextElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 0.f, 0.f },
        "Defeat...",
        72
    );

    sf::FloatRect textBounds = title->getText().getLocalBounds();
    title->getText().setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
        });
    title->setPosition({ 1920.f / 2.f, 1080.f / 2.f });

    auto menuButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 20.f, 1080.f - 100.f - 20.f },
        "MENU"
    );
    menuButton->setCallback([this]() {
        /* deferred action example */
        });

    auto mapButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 150.f, 1080.f - 100.f - 20.f },
        "MAP"
    );
    mapButton->setCallback([this]() {
        /* deferred action example */
        });

    addUIElement(title);
    addUIElement(menuButton);
    addUIElement(mapButton);
}

// Check if mouse is over any UI element
bool UIManager::isMouseOverUI(const sf::Vector2i& worldPosition) const
{
    for (auto& e : m_uiElements)
    {
        if (!e) continue;
        sf::FloatRect b = e->getBounds();
        if (b.contains(static_cast<sf::Vector2f>(worldPosition))) return true;
    }
    return false;
}
