#pragma once

#include "../systems/ColliderSpace.h"

#include <vector>

class DebugRenderer 
{
public:

    struct Options 
    {
        Options(int frame = 1, sf::Color const& color = sf::Color::Green);
    
        int frame;
        sf::Color color;
    };

    void drawRaycast(Raycast const& r, Options const& options = Options());
    void drawText(sf::Text const& text, Options const& options = Options());

    void draw(sf::RenderTarget& renderer);

private:

    struct ToDraw 
    {
        ToDraw(Raycast const& r, Options const& o);
        ToDraw(sf::Text const& t, Options const& o);
        ToDraw(ToDraw const& t);
        ~ToDraw();
        ToDraw& operator=(ToDraw const& t);
        
        enum class Type 
        { 
            Raycast, 
            Text 
        } type;

        union 
        {
            Raycast raycast;
            sf::Text text;
        };
        Options options;
    };

    std::vector<ToDraw> m_toDraw;
};