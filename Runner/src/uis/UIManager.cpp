#include "UIManager.h"

#include "UIButtonElement.h"
#include "UITextElement.h"
#include "UITextureElement.h"
#include "UIGameStatsText.h"
#include "UIFinalScoreTextElement.h"

#include "../core/Game.h"

#include <iostream>


UIManager::UIManager(Game* game) : m_game(game) 
{

}


void UIManager::initGameStats(GameStats* gameStats)
{
    m_gameStats = gameStats;
}

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
void UIManager::renderUIs(sf::RenderWindow& window)
{
    for (auto& element : m_uiElements)
        element->render(window);
}

// Handle input events for all UI elements
void UIManager::handleUIEvents(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& uiElement : m_uiElements)
    {
        if (!uiElement) continue;
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
            m_game->Running = true;
            if (m_game->Running) {
                m_pendingAction = [this]() {
                    std::cout << "play!!!" << std::endl;
                generateInGameUIs();
                };
            }
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
            m_game->Quit = true;
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



// Generate defeat UI layout
void UIManager::generateDefeatUIs()
{
    m_uiElements.clear();

    auto bg = std::make_shared<UITextureElement>(
        sf::Vector2f{ 1920.f, 1080.f },
        sf::Vector2f{ 0.f,0.f },
        "assets/textures/background/runnerBG.png"
    );

    auto title = std::make_shared<UITextElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 1920.f/2.f - 350, 1080.f / 2.f - 200},
        "Defeat...\nFinal Score : " + std::to_string((int)m_gameStats->getFinalScore()),
        72
    );

    auto menuButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 20.f, 1080.f - 100.f - 20.f },
        "MENU"
    );
    menuButton->setCallback([this]() {
		m_game->Running = false;
        });


    addUIElement(bg);
    addUIElement(title);
    addUIElement(menuButton);
}

void UIManager::generateInGameUIs()
{
    m_uiElements.clear();

    auto score = std::make_shared<UIGameStatsText>(
        m_gameStats
    );

    addUIElement(score);
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
