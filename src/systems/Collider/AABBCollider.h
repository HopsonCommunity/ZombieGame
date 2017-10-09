#pragma once 

#include "SAT_Collider.h"

class AABBCollider : public SAT_Collider {
public:

    AABBCollider();
    AABBCollider(sf::Vector2f const& origin, sf::Vector2f const& dimension);
    virtual ~AABBCollider();

    std::vector<sf::Vector2f> getPoints() const override;
    std::vector<sf::Vector2f> getNormals() const override;
    Projection project(sf::Vector2f const& normal) const override;

private:

    std::vector<sf::Vector2f> points;

};