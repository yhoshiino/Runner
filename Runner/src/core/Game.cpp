#include "Game.h"

Game::Game()
{
    m_window.create(sf::VideoMode(m_logicalResolution), "Robot Runner", sf::State::Fullscreen);
    m_levelManager = std::make_unique<LevelManager>();
    m_entityManager = std::make_unique<EntityManager>();
}

Game::~Game()
{
	shutDown();
}

void Game::run()
{


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

        m_window.clear();

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
