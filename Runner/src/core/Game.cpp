#include "Game.h"

Game::Game()
{
    m_window.create(sf::VideoMode(m_logicalResolution), "Robot Runner", sf::State::Fullscreen);
    m_entityManager = std::make_unique<EntityManager>();
    m_levelManager = std::make_unique<LevelManager>(m_entityManager.get());
}

Game::~Game()
{
	shutDown();
}

void Game::run()
{
    // Temporary shapes
    sf::RectangleShape conveyor({1920.f, 504 });
    conveyor.setFillColor(sf::Color(150, 150, 150));

    sf::RectangleShape fire({ 300.f, 1080.f });
    fire.setFillColor(sf::Color(255, 124, 70));

    conveyor.setPosition({ fire.getSize().x, 576 / 2.f});

	m_levelManager->load(1);

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
            
        }

        m_entityManager->updateAll(m_deltatime);
        m_entityManager->resetPlayerPosition();
        m_window.clear();
        m_window.draw(conveyor);
        m_window.draw(fire);

        m_window.draw(conveyor);
        m_window.draw(fire);
        m_entityManager->drawAll(m_window);

        m_window.display();
    }
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
