#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <algorithm>

struct Projection {
    float first;
    float second;

    float size() const { return second - first; }

    static bool overlap(Projection const& p0, Projection const& p1) {
        assert(p0.first < p0.second);
        assert(p1.first < p1.second);
        return !(
            (p1.first < p0.first && p1.second < p0.first) ||
            (p1.first > p0.second && p1.second > p0.second)
        );
    }

    static Projection overlap_area(Projection const& p0, Projection const& p1) {
        // assume there are overlaping
        assert(overlap(p0, p1));
        return { std::max(p0.first, p1.first), std::min(p0.second, p1.second) };
    }
};

class SAT_Collider {
public:

    virtual ~SAT_Collider() {}

    virtual std::vector<sf::Vector2f> getPoints(sf::Vector2f const& offset = sf::Vector2f(0, 0)) const = 0;
    virtual std::vector<sf::Vector2f> getNormals() const = 0;
    virtual Projection project(sf::Vector2f const& normal, sf::Vector2f const& offset) const = 0;
};