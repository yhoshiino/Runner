#include "CollisionUtils.h"

static float Cross(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB)
{
    return vectorA.x * vectorB.y - vectorA.y * vectorB.x;
}

bool utils::linesIntersect(const sf::Vector2f& segment1Start, const sf::Vector2f& segment1End, 
                           const sf::Vector2f& segment2Start, const sf::Vector2f& segment2End)
{
    // Calculate direction vectors for each segment
    const sf::Vector2f segment1Direction = segment1End - segment1Start;
    const sf::Vector2f segment2Direction = segment2End - segment2Start;

    const float denominator = Cross(segment1Direction, segment2Direction);
    if (denominator == 0.0f)
        return false; // The segments are parallel or collinear

    // Vector between the two start points
    const sf::Vector2f betweenStarts = segment2Start - segment1Start;

    const float segment1Factor = Cross(betweenStarts, segment2Direction) / denominator;
    const float segment2Factor = Cross(betweenStarts, segment1Direction) / denominator;

    // Both factors must be between 0 and 1 for intersection to occur within both segments
    const bool intersects =
        (segment1Factor >= 0.0f && segment1Factor <= 1.0f) &&
        (segment2Factor >= 0.0f && segment2Factor <= 1.0f);

    return intersects;
}

bool utils::lineIntersectsRect(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd, const sf::FloatRect& rect)
{
    // Get rectangle corners
    const sf::Vector2f topLeft = rect.position;
    const sf::Vector2f topRight = rect.position + sf::Vector2f{rect.size.x, 0.0f};
    const sf::Vector2f bottomRight = rect.position + rect.size;
    const sf::Vector2f bottomLeft = rect.position + sf::Vector2f{0.0f, rect.size.y};

    // Check intersection with each rectangle edge
    if (linesIntersect(lineStart, lineEnd, topLeft, topRight)) return true;
    if (linesIntersect(lineStart, lineEnd, topRight, bottomRight)) return true;
    if (linesIntersect(lineStart, lineEnd, bottomRight, bottomLeft)) return true;
    if (linesIntersect(lineStart, lineEnd, bottomLeft, topLeft)) return true;

    // Also check if the line end point is inside the rectangle
    if (rect.contains(lineEnd))
        return true;

    return false;
}
