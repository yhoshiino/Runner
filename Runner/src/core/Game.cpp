#include "Game.h"

Game::Game(): m_uiManager(std::make_unique<UIManager>(this)),
              m_conveyorSprite1(m_conveyorTexture), m_conveyorSprite2(m_conveyorTexture), m_factorySprite(m_factoryTexture), m_fireSprite(m_fireTexture)
{
    m_window.create(sf::VideoMode(m_LOGICAL_RESOLUTION), "Robot Runner", sf::State::Fullscreen);
    m_gameStats = std::make_unique<GameStats>();
    m_entityManager = std::make_unique<EntityManager>(m_gameStats.get());
    m_levelManager = std::make_unique<LevelManager>(m_entityManager.get());

    // Init seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    initGraphics();
    m_uiManager->initGameStats(m_gameStats.get());
    initViews();
}

Game::~Game()
{
	shutDown();
}


void Game::run()
{
    m_window.setView(m_gameView);


    while (m_window.isOpen())
    {
        m_deltatime = m_deltaClock.restart().asSeconds();

        // Poll Events
        pollEvents();

        //std::cout << "[SCORE]: " << std::ceil(m_gameStats->getScore()) << std::endl;

        // Update
        if (m_gameState == GameState::PLAYING)
        {
            // Spawn random entitites
            m_entityManager->spawnEntitiesRandomly(1 + std::rand() % 2, m_deltatime);

            // Updating
            m_gameStats->updateConveyorSpeed(m_deltatime);
            m_gameStats->updateDistance(m_deltatime);

            m_uiManager->updateUIs(m_deltatime);

            m_entityManager->updateAll(m_deltatime);
            updateGameGraphics();

            //std::cout << "[SCORE]: " << std::ceil(m_gameStats->getScore()) << std::endl;
        }

        // Rendering
        m_window.clear();

        if (Quit) {
            m_window.close();
        }

        if (Running)
            m_gameState = GameState::PLAYING;
        else
        {
            m_entityManager->resetPlayerPosition();
            m_gameState = GameState::MAIN_MENU;
        }

        if (m_entityManager->playerOnFire())
            m_gameState = GameState::DEFEAT;

        if (m_gameState == GameState::MAIN_MENU)
            m_uiManager->generateMainMenuUIs();

        if (m_gameState == GameState::PLAYING)
        {
            drawGameGraphics();
            m_entityManager->drawAll(m_window);
        }

        if (m_gameState == GameState::DEFEAT) {
            std::cout << "defeat" << std::endl;
            m_uiManager->generateDefeatUIs();
            m_gameStats->resetStats();
            m_entityManager->clearGameObjects();
        }
            

        m_uiManager->renderUIs(m_window);
        m_window.display();
    }
}

void Game::initGraphics()
{
    auto isConveyorTextureLoaded = m_conveyorTexture.loadFromFile("assets/textures/sprites/conveyor.png");
    auto isFireTextureLoaded = m_fireTexture.loadFromFile("assets/textures/sprites/fire_pit.png");
    auto isFactoryTextureLoaded = m_factoryTexture.loadFromFile("assets/textures/sprites/factory.png");

    // Reseting texture rect
    m_conveyorSprite1.setTexture(m_conveyorTexture, true); // True = reseting texture rect
    m_conveyorSprite2.setTexture(m_conveyorTexture, true);
    m_fireSprite.setTexture(m_fireTexture, true);
    m_factorySprite.setTexture(m_factoryTexture, true);

    // Scaling
    m_conveyorSprite1.setScale({ 8.f, 8.f });
    m_conveyorSprite2.setScale({ 8.f, 8.f });
    m_fireSprite.setScale({ 8.f, 8.f });
    m_factorySprite.setScale({ 5.f, 5.f });

    // Init sprite positions
    m_conveyorSprite1.setPosition({ 0.f, 576 / 2.f });
    m_conveyorSprite2.setPosition({ m_conveyorSprite1.getGlobalBounds().size.x, 576 / 2.f });
    m_fireSprite.setPosition({ 0.f, 0.f });
    m_factorySprite.setPosition({ m_fireSprite.getGlobalBounds().size.x, 0.f });
}

void Game::initViews()
{
    m_gameView.setSize(static_cast<sf::Vector2f>(m_LOGICAL_RESOLUTION));
    m_gameView.setCenter(m_gameView.getSize() / 2.f);

    m_gameView.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }));
}

void Game::shutDown()
{
}

void Game::pollEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                m_window.close();
        }

        // Handles buttons events, etc...
        m_uiManager->handleUIEvents(*event, m_window);
    }
}

void Game::centerWindow()
{
}

void Game::updateGameGraphics()
{
    m_conveyorSprite1.move(sf::Vector2f{ -m_gameStats->getConveyorSpeed() * m_deltatime, 0.f });
    m_conveyorSprite2.move(sf::Vector2f{ -m_gameStats->getConveyorSpeed() * m_deltatime, 0.f });

    if (m_conveyorSprite1.getPosition().x + m_conveyorSprite1.getGlobalBounds().size.x < 0.f)
        m_conveyorSprite1.setPosition({ m_conveyorSprite2.getPosition().x + m_conveyorSprite2.getGlobalBounds().size.x, 576 / 2.f });

    if (m_conveyorSprite2.getPosition().x + m_conveyorSprite2.getGlobalBounds().size.x < 0.f)
        m_conveyorSprite2.setPosition({ m_conveyorSprite1.getPosition().x + m_conveyorSprite1.getGlobalBounds().size.x, 576 / 2.f });
}

void Game::drawGameGraphics()
{
    m_window.draw(m_factorySprite);
    m_window.draw(m_conveyorSprite1);
    m_window.draw(m_conveyorSprite2);
    m_window.draw(m_fireSprite);
}

int Game::getSeed() const
{
    return m_seed;
}
