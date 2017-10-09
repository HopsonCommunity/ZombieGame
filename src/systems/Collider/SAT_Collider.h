#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

struct Projection {
    float first;
    float second;

    operator float() const { float d = second - first; return d < 0 ? -d : d; }

    static bool overlap(Projection const& p0, Projection const& p1) {
        float f0, f1, s0, s1;
        if (p0.first < p0.second) {
            f0 = p0.first;
            s0 = p0.second;
        } else {
            f0 = p0.second;
            s0 = p0.first;
        }
        if (p1.first < p1.second) {
            f1 = p1.first;
            s1 = p1.second;
        } else {
            f1 = p1.second;
            s1 = p1.first;
        }
        return s0 < f1 || f0 > s1 || s1 < f0 || f1 > s0;
    }

    static Projection overlap_area(Projection const& p0, Projection const& p1) {
        float f0, f1, s0, s1;
        if (p0.first < p0.second) {
            f0 = p0.first;
            s0 = p0.second;
        } else {
            f0 = p0.second;
            s0 = p0.first;
        }
        if (p1.first < p1.second) {
            f1 = p1.first;
            s1 = p1.second;
        } else {
            f1 = p1.second;
            s1 = p1.first;
        }
        if (f0 < f1) {
            if (s0 < s1)
                return { f1, s0 };
            else
                return { f1, s1 };
        } else {
            if (s0 < s1)
                return { f0, s0 };
            else
                return { f0, s1 };
        }
    }
};

class SAT_Collider {
public:

    virtual ~SAT_Collider();

    virtual std::vector<sf::Vector2f> getPoints() const = 0;
    virtual std::vector<sf::Vector2f> getNormals() const = 0;
    virtual Projection project(sf::Vector2f const& normal) const = 0;
};