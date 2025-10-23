#include "LevelManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

LevelManager::LevelManager() 
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::load(int levelUID)
{
	std::cout << "Loading level " << levelUID << ":" << std::endl;
	parseLevelFile("src/core/level_test.txt");
	spawnLevelEntities();

	m_isLoaded = true;
}

void LevelManager::unload()
{
	m_isLoaded = false;
}

void LevelManager::renderBackground()
{
}

bool LevelManager::isloaded()
{
	return m_isLoaded;
}

void LevelManager::parseLevelFile(const std::string& filePath)
{
	if(!m_entitySpawnDataList.empty())
		m_entitySpawnDataList.clear();

	std::ifstream levelFile(filePath);
	if(!levelFile.is_open())
	{
		std::cerr << "Failed to open level file: " << filePath << std::endl;
		return;
	}

	std::string line;
	while(std::getline(levelFile, line))
	{
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		// Ignore comments or empty lines
		if (line.empty() || line[0] == '#') // Comment lines start with '#' : # This is a file comment
			continue;

		size_t colonPos = line.find(':');
		if(colonPos == std::string::npos)
		{
			std::cerr << "Invalid line format (missing ':'): " << line << std::endl;
			continue;
		}

		// Extract type (before ':')
		std::string type = line.substr(0, colonPos);
		// Extract parameters (after ':')
		std::string parameters = line.substr(colonPos + 1);

		// Removes spaces
		type.erase(std::remove_if(type.begin(), type.end(), ::isspace), type.end());

		if (type == "ENTITY")
		{
			EntitySpawnData spawnData;

			// Find UID
			size_t uidPos = parameters.find("uid=");
			if(uidPos == std::string::npos)
			{
				std::cerr << "Missing 'uid' in ENTITY line: " << line << std::endl;
				continue;
			}
			else
			{
				size_t start = uidPos + 4;
				size_t end = parameters.find(';', start);
				spawnData.entityUID = std::stoi(parameters.substr(start, end - start));
			}

			// Find Position
			size_t posPos = parameters.find("position=");
			if(posPos == std::string::npos)
			{
				std::cerr << "Missing 'pos' in ENTITY line: " << line << std::endl;
				continue;
			}
			else
			{
				size_t start = posPos + 10;
				size_t end = parameters.find('}', start);
				std::string coords = parameters.substr(start, end - start);

				std::replace(coords.begin(), coords.end(), ',', ' ');
				std::istringstream coordStream(coords);
				coordStream >> spawnData.spawnPosition.x >> spawnData.spawnPosition.y;
			}

			m_entitySpawnDataList.push_back(spawnData);
		}
		else
		{
			std::cerr << "Unknown line type: " << type << std::endl;
		}
	}

	levelFile.close();
}

void LevelManager::spawnLevelEntities()
{
	for(const auto& spawnData : m_entitySpawnDataList)
	{
		// Here you would call the entity manager to create the entity
		// EntityManager::spawnEntity(spawnData.entityUID, spawnData.spawnPosition);

		std::cout << "Spawning entity UID: " << spawnData.entityUID 
				  << " at position: (" << spawnData.spawnPosition.x 
				  << ", " << spawnData.spawnPosition.y << ")" << std::endl;
	}
}
