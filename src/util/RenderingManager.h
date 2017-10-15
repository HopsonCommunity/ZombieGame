#pragma once

#include "Renderer.h"

#include <vector>
#include <functional>

class RenderingManager
{
    public:
        RenderingManager(Renderer* renderer);

        enum ZIndex : int
        {
            BACKGROUND = -255,
            MIDDLEGROUND = 0,
            FOREGROUND = 255,

            HUD = 2048
        };

        void draw(std::pair<int, std::function<void(Renderer&)>>);

        void render();

        Renderer* getRenderer();

    private:
        std::vector<std::pair<int, std::function<void(Renderer&)>>> m_drawCallbacks;

        Renderer* m_renderer;
};
