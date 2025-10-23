#include "EntityManager.h"
#include <memory>

EntityManager::EntityManager(): 
	m_player(std::make_unique<Player>(sf::Vector2f{ 700.f, 540.f }))
{
	
}

EntityManager::~EntityManager()
{
}

void EntityManager::updateAll(float deltatime) {
	m_player->update(deltatime);
}

void EntityManager::drawAll(sf::RenderWindow& window) {
	m_player->draw(window);
}

void EntityManager::updateColisions() {

}

void EntityManager::spawnEntity(int entityUID, sf::Vector2f position) {

}

void EntityManager::resetPlayerPosition() {
	if (m_player->isOnFire()) {
		m_player->resetPlayer();
	}
}