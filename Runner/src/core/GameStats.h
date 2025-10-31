#pragma once

class GameStats
{
public:

	GameStats() = default;

	void updateConveyorSpeed(float deltaTime);
	void updateDistance(float meter, float deltaTime);

	float getConveyorSpeed() const;
	float getDistance() const;
	float getScore() const;

private:

	float m_score = 0;
	float m_distance = 0.f; // Distance in meters
	float m_conveyorSpeed = 300.f;
	
	const float m_CONVEYOR_ACCELERATION_FACTOR = 5.f;
};