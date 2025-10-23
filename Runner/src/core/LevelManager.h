#pragma once
#include <SFML/Graphics.hpp>

struct EntitySpawnData
{
	int entityUID = -1;
	sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f);
};

class LevelManager
{
public:

	LevelManager();
	~LevelManager();

	void load(int levelUID);
	void unload();
	void renderBackground();
	bool isloaded();
	void parseLevelFile(const std::string& filePath);
	void spawnLevelEntities();

private:

	int m_currentLevelUID = -1;

	bool m_isLoaded = false;

	float m_elapsedTime = 0.f;

	std::vector<EntitySpawnData> m_entitySpawnDataList;

	/*sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;*/
};