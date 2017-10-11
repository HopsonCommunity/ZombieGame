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

std::vector<sf::Vector2f> AABBCollider::getPoints(sf::Vector2f const& offset) const {
    auto pts = points;
    for(auto& v : pts) v += offset;
    return pts;
}

std::vector<sf::Vector2f> AABBCollider::getNormals() const {
    return {
        { 0, 1 },
        { 1, 0 }
    };
}

Projection AABBCollider::project(sf::Vector2f const& normal, sf::Vector2f const& offset) const {
    auto p = points[0] + offset;
    float min = p.x * normal.x + p.y * normal.y;
    float max = p.x * normal.x + p.y * normal.y;

    for(int i = 1; i < 4; ++i) {
        p = points[i] + offset;
        float dot = p.x * normal.x + p.y * normal.y;
        if (dot < min) min = dot;
        if (dot > max) max = dot;
    }
    return { min, max };
};

sf::Vector2f AABBCollider::getOrigin() const {
    return points[0];
}

sf::Vector2f AABBCollider::getDimension() const {
    return points[2] - points[0];
}
