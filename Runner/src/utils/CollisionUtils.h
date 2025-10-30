#pragma once
#include <SFML/Graphics.hpp>

namespace utils
{
	// Test if two line segments intersect
	bool linesIntersect(const sf::Vector2f& segment1Start, const sf::Vector2f& segment1End, 
						const sf::Vector2f& segment2Start, const sf::Vector2f& segment2End);

	// Test if a line segment intersects a rectangle
	bool lineIntersectsRect(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd, const sf::FloatRect& rect);
}