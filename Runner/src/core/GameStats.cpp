#include "GameStats.h"

void GameStats::updateConveyorSpeed(float deltaTime)
{
    m_conveyorSpeed += m_CONVEYOR_ACCELERATION_FACTOR * deltaTime;
}

void GameStats::updateDistance(float meter, float deltaTime)
{
    m_distance += meter;
    m_score += m_distance * deltaTime * 0.01f;
}

float GameStats::getConveyorSpeed() const
{
    return m_conveyorSpeed;
}

float GameStats::getDistance() const
{
    return m_distance;
}

float GameStats::getScore() const
{
    return m_score;
}

float GameStats::getFinalScore()
{
    m_finalscore += m_score;
    return m_finalscore;
}
