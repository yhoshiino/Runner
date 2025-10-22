#pragma once
#include <SFML/Graphics.hpp>

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

	bool m_isload;
	int m_currentLevelUID;
	float m_elapseTime;
	/*sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;*/


};