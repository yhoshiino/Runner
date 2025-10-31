#include "GameStats.h"

void GameStats::updateConveyorSpeed(float deltaTime)
{
    m_conveyorSpeed += m_CONVEYOR_ACCELERATION_FACTOR * deltaTime;
}

void GameStats::updateDistance(float deltaTime)
{
    const float METER_IN_PIXELS = 200.f;

    float distanceThisFrame = (m_conveyorSpeed * deltaTime) / METER_IN_PIXELS;
    m_distance += distanceThisFrame;

    m_score += distanceThisFrame * 5.5f; // So it seems a bit random
}

void GameStats::resetStats()
{
    m_score = 0.f;
    m_distance = 0.f;
    m_conveyorSpeed = m_START_CONVEYOR_SPEED;
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
