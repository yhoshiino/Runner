#include "Game.h"

Game::Game()
{
    m_window.create(sf::VideoMode(m_logicalResolution), "Robot Runner");
    m_gameStats = std::make_unique<GameStats>();
    m_entityManager = std::make_unique<EntityManager>(m_gameStats.get());
    m_levelManager = std::make_unique<LevelManager>(m_entityManager.get());

    initViews();
}

Game::~Game()
{
	shutDown();
}

void Game::run()
{
    // Temporary spawner
    const float spawnDistance = 350.f;
    float spawnAccumulator = 0.f;

    // Temporary shapes
	sf::Texture conveyorTexture;
	sf::Sprite conveyorSprite1(conveyorTexture);
	sf::Sprite conveyorSprite2(conveyorTexture);
	auto isLoaded = conveyorTexture.loadFromFile("assets/textures/sprites/conveyor.png");
	conveyorSprite1.setTexture(conveyorTexture, true);
    conveyorSprite2.setTexture(conveyorTexture, true);
	conveyorSprite1.setScale({ 8.f, 8.f });
    conveyorSprite2.setScale({ 8.f, 8.f });

    sf::RectangleShape fire({ 300.f, 1080.f });
    fire.setFillColor(sf::Color(255, 124, 70));

    conveyorSprite1.setPosition({ 0.f, 576 / 2.f });
    conveyorSprite2.setPosition({ conveyorSprite1.getGlobalBounds().size.x, 576 / 2.f});

	m_levelManager->load(1);

    m_window.setView(m_gameView);

    while (m_window.isOpen())
    {
        m_deltatime = m_deltaClock.restart().asSeconds();

        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    m_window.close();
            }
            m_uiManager.handleUIEvents(*event, m_window);
        }
        // TEMPORARY handle game state/change window
        /*
        if (m_gameState == GameState::MainMenu)
        {
            m_uiManager.generateMainMenuUIs();

            if (m_uiManager.isPlayButtonPressed())
            {
                m_gameState = GameState::Playing;
                m_levelManager->load(1);
            }

            m_uiManager.renderUIs(m_window);
        }*/


        m_gameStats->updateConveyorSpeed(m_deltatime);
        m_gameStats->updateDistance(0.2f, m_deltatime);

        //std::cout << "[SCORE]: " << std::ceil(m_gameStats->getScore()) << std::endl;

        // TEMPORARY SPAWN
        spawnAccumulator += m_gameStats->getConveyorSpeed() * m_deltatime;
        if (spawnAccumulator >= spawnDistance)
        {
            spawnAccumulator = 0.f;

            // Spawn between 1 and 5 entities
            int entitiesToSpawn = 1 + (rand() % 5); // rand()%5 -> 0 à 4, +1 -> 1 à 5

            for (int i = 0; i < entitiesToSpawn; ++i)
            {
                float y = 288.f + static_cast<float>(rand() % (720 - 288 + 1));
                m_entityManager->spawnEntity({ 2000.f, y });
                m_entityManager->spawnCollectible(sf::Vector2f{ 2000.f - 100, y }, 't');
            }
        }
		//m_uiManager.updateUIs(m_deltatime);
        m_entityManager->updateAll(m_deltatime);

		conveyorSprite1.move(sf::Vector2f{ -m_gameStats->getConveyorSpeed() * m_deltatime, 0.f });
		conveyorSprite2.move(sf::Vector2f{ -m_gameStats->getConveyorSpeed() * m_deltatime, 0.f });

        if(conveyorSprite1.getPosition().x + conveyorSprite1.getGlobalBounds().size.x < 0.f)
            conveyorSprite1.setPosition({ conveyorSprite2.getPosition().x + conveyorSprite2.getGlobalBounds().size.x, 576 / 2.f });

        if (conveyorSprite2.getPosition().x + conveyorSprite2.getGlobalBounds().size.x < 0.f)
            conveyorSprite2.setPosition({ conveyorSprite1.getPosition().x + conveyorSprite1.getGlobalBounds().size.x, 576 / 2.f });
		
        m_entityManager->resetPlayerPosition();
        m_window.clear();
		//m_uiManager.renderUIs(m_window);
        //if (m_gameState == GameState::Playing) {
            //m_window.draw(conveyor);
            m_window.draw(conveyorSprite1);
            m_window.draw(conveyorSprite2);
            m_window.draw(fire);

            m_entityManager->drawAll(m_window);
        //}
        

        m_window.display();
    }
}

void Game::initViews()
{
    m_gameView.setSize(static_cast<sf::Vector2f>(m_logicalResolution));
    m_gameView.setCenter(m_gameView.getSize() / 2.f);

    m_gameView.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }));
}

void Game::shutDown()
{
}

void Game::pollEvents()
{
}

void Game::centerWindow()
{
}
