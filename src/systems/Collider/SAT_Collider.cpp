#include "SAT_Collider.h"

float Projection::size() const 
{ 
    return second - first; 
}

bool Projection::overlap(Projection const& p0, Projection const& p1) 
{
    assert(p0.first < p0.second);
    assert(p1.first < p1.second);
    return !(
        (p1.first < p0.first && p1.second < p0.first) ||
        (p1.first > p0.second && p1.second > p0.second)
    );
}

Projection Projection::overlap_area(Projection const& p0, Projection const& p1) 
{
    assert(overlap(p0, p1));
    return { std::max(p0.first , p1.first )
        ,    std::min(p0.second, p1.second) };
}
