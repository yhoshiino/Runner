#include "Game.h"

Game::Game()
{
    m_window.create(sf::VideoMode({ 500, 500 }), "Robot Runner");
}

Game::~Game()
{
	shutDown();
}

void Game::run()
{
    // Green Circle Test
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
        }

        m_window.clear();
        m_window.draw(shape);
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
