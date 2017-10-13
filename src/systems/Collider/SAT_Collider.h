#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <cassert>

struct Projection 
{
    float first;
    float second;

    float size() const;
    
    static bool overlap(Projection const& p0, Projection const& p1);
    static Projection overlap_area(Projection const& p0, Projection const& p1);
};

class SAT_Collider 
{
public:

    virtual ~SAT_Collider() {}

    virtual std::vector<sf::Vector2f> getPoints(sf::Vector2f const& offset = sf::Vector2f(0, 0)) const  = 0;
    virtual std::vector<sf::Vector2f> getNormals() const                                                = 0;
    virtual Projection project(sf::Vector2f const& normal, sf::Vector2f const& offset) const            = 0;
};