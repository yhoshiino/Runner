#include "UIManager.h"



#include <iostream>



// Add a UI element to the manager
void UIManager::add_ui_element(std::shared_ptr<UIElement> element)
{
    m_uiElements.push_back(element);
}

// Update all UI elements (called each frame)
void UIManager::update_uis(float deltaTime)
{
    for (auto& element : m_uiElements)
    {
        element->update(deltaTime);
    }
}

// Render all UI elements
// Handles world-space vs screen-space rendering by switching the view as needed
void UIManager::render_uis(sf::RenderWindow& window, sf::View& uiView, sf::View& worldView)
{
    for (auto& element : m_uiElements)
    {
        if (element->isWorldSpaceUi)
        {
            window.setView(worldView);
            element->render(window);
            window.setView(uiView);
        }
        else
        {
            element->render(window);
        }
    }
}

// Handle input events for all UI elements
// Executes deferred actions after processing events
void UIManager::handle_ui_events(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& uiElement : m_uiElements)
    {
        uiElement->handle_event(event, window);
    }

    // Execute deferred action if set by button callbacks
    if (m_pendingAction)
    {
        auto action = m_pendingAction;
        m_pendingAction = nullptr;
        action();
    }
}









void UIManager::generate_victory_uis()
{
    m_uiElements.clear();


    // Victory Text
    auto title = std::make_shared<UITextElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 0.f, 0.f },
        "Victory!",
        72
    );

    sf::FloatRect textBounds = title->get_text().getLocalBounds();
    title->get_text().setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
        });
    title->set_position({ 1920.f / 2.f, 1080.f / 2.f });

    // Rewards
    int gainedShells = 0;
    bool isNewUnitAvailable = false;

    

    // Shells Reward Text
    auto shellRewardText = std::make_shared<UITextElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 0.f, 0.f },
        '+' + std::to_string(gainedShells) + " ¤",
        60
    );

    sf::FloatRect shellsTextBound = shellRewardText->get_text().getLocalBounds();
    shellRewardText->get_text().setOrigin({
        shellsTextBound.position.x + shellsTextBound.size.x / 2.f,
        shellsTextBound.position.y + shellsTextBound.size.y / 2.f
        });
    shellRewardText->set_position({ 1920.f / 2.f, 1080.f / 2.f + 100.f });

    shellRewardText->set_text_color(sf::Color(0, 255, 255, 255));

    // New Unit Available Text
    auto newUnitText = std::make_shared<UITextElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 0.f, 0.f },
        "A NEW UNIT IS AVAILABLE IN THE UPGRADES MENU!",
        46
    );

    sf::FloatRect unitTextBound = newUnitText->get_text().getLocalBounds();
    newUnitText->get_text().setOrigin({
        unitTextBound.position.x + unitTextBound.size.x / 2.f,
        unitTextBound.position.y + unitTextBound.size.y / 2.f
        });
    newUnitText->set_position({ 1920.f / 2.f, 1080.f / 2.f + 200.f });

    if (isNewUnitAvailable)
        newUnitText->set_text_color(sf::Color(255, 0, 255, 255));
    else
        newUnitText->set_text_color(sf::Color(255, 0, 255, 0));


    // Back to menu button
    auto menuButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 20.f, 1080.f - 100.f - 20.f },
        "MENU"
    );
    menuButton->set_callback([this]()
        {
            /*m_pendingAction = [this]() {
                if (auto stage = m_stage.lock())
                {
                    m_stage.lock()->unload();
                }
            };*/
        });

    //back to map button
    auto mapButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 150.f, 1080.f - 100.f - 20.f },
        "MAP"
    );
    mapButton->set_callback([this]()
        {
            /*m_pendingAction = [this]() {
                if (auto stage = m_stage.lock())
                {
                    m_stage.lock()->unload();
                }
            };*/
        });

    add_ui_element(title);
    add_ui_element(shellRewardText);
    add_ui_element(newUnitText);

    add_ui_element(menuButton);
    add_ui_element(mapButton);
}

void UIManager::generate_defeat_uis()
{
    m_uiElements.clear();

    // Victory Text
    auto title = std::make_shared<UITextElement>(
        sf::Vector2f{ 200.f, 100.f },
        sf::Vector2f{ 0.f, 0.f },
        "Defeat...",
        72
    );

    sf::FloatRect textBounds = title->get_text().getLocalBounds();
    title->get_text().setOrigin({
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f
        });
    title->set_position({ 1920.f / 2.f, 1080.f / 2.f });

    //back to menu button
    auto menuButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 20.f, 1080.f - 100.f - 20.f },
        "MENU"
    );
    menuButton->set_callback([this]()
        {
            /*m_pendingAction = [this]() {
                if (auto stage = m_stage.lock())
                {
                    m_stage.lock()->unload();
                }
            };*/
        });

    //back to map button
    auto mapButton = std::make_shared<UIButtonElement>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 150.f, 1080.f - 100.f - 20.f },
        "MAP"
    );
    mapButton->set_callback([this]()
        {
            /*m_pendingAction = [this]() {
                if (auto stage = m_stage.lock())
                {
                    m_stage.lock()->unload();
                }
            };*/
        });

    add_ui_element(title);
    add_ui_element(menuButton);
    add_ui_element(mapButton);
}

bool UIManager::is_mouse_over_ui(const sf::Vector2i& worldPosition) const
{
    for (auto& e : m_uiElements)
    {
        if (!e) continue;
        sf::FloatRect b = e->get_bounds();
        if (b.contains(static_cast<sf::Vector2f>(worldPosition))) return true;
    }
    return false;
}