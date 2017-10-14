#pragma once 

#include "SAT_Collider.h"

class AABBCollider : public SAT_Collider 
{
public:

    AABBCollider(sf::Vector2f const& origin, sf::Vector2f const& dimension);
    AABBCollider();
    virtual ~AABBCollider();

    std::vector<sf::Vector2f> getPoints(sf::Vector2f const& offset = sf::Vector2f(0, 0)) const override;
    std::vector<sf::Vector2f> getNormals() const override;
    Projection project(sf::Vector2f const& normal, sf::Vector2f const& offset) const override;

    sf::Vector2f getOrigin() const;
    sf::Vector2f getDimension() const;
    
private:

    std::vector<sf::Vector2f> m_points;

};