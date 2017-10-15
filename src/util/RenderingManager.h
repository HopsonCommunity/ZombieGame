#pragma once

#include "Renderer.h"

#include <vector>
#include <functional>

class RenderingManager : public Renderer
{
    public:
        RenderingManager(sf::RenderTarget& renderer);

        enum ZIndex : int
        {
            BACKGROUND = -255,
            MIDDLEGROUND = 0,
            FOREGROUND = 255,

            HUD = 2048
        };

        void draw(std::pair<int, std::function<void(Renderer&)>>);

        void render();

    private:
        std::vector<std::pair<int, std::function<void(Renderer&)>>> m_drawCallbacks;
};
