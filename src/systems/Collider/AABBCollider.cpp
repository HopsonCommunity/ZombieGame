#include "AABBCollider.h"

AABBCollider::AABBCollider() : AABBCollider({0, 0}, {0, 0}) {}
AABBCollider::AABBCollider(sf::Vector2f const& origin, sf::Vector2f const& dimension) 
    : points({
        { origin.x, origin.y },
        { origin.x + dimension.x, origin.y },
        { origin.x + dimension.x, origin.y + dimension.y },
        { origin.x, origin.y + dimension.y }
    }) {}

AABBCollider::~AABBCollider() {}

std::vector<sf::Vector2f> AABBCollider::getPoints() const {
    return points;
}

std::vector<sf::Vector2f> AABBCollider::getNormals() const {
    return {
        { 1, 0 },
        { 0, 1 },
        { -1, 0 },
        { 0, -1 }
    };
}

Projection AABBCollider::project(sf::Vector2f const& normal) const {
    float min = points[0].x * normal.x + points[0].y * normal.y;
    float max = points[0].x * normal.x + points[0].y * normal.y;

    for(int i = 1; i < 4; ++i) {
        float dot = points[i].x * normal.x + points[i].y * normal.y;
        if (dot < min) min = dot;
        if (dot > max) max = dot;
    }
    return { min, max };
};