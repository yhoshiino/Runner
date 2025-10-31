#pragma once

class GameStats
{
public:

	GameStats() = default;

	void updateConveyorSpeed(float deltaTime);
	void updateDistance(float deltaTime);

	void addScore(int scoreToAdd);
	void resetStats();

	float getConveyorSpeed() const;
	float getDistance() const;
	float getScore() const;
	float getFinalScore();

private:

	float m_score = 0;
	float m_distance = 0.f; // Distance in meters

	float m_finalscore = 0.f;
	
	const float m_CONVEYOR_ACCELERATION_FACTOR = 5.f;
	const float m_START_CONVEYOR_SPEED = 300.f;
	float m_conveyorSpeed = 300.f;
};