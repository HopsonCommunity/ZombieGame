#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Renderer
{
public:

    Renderer(sf::RenderTarget& renderer);
    Renderer();

    enum ZIndex : int
    {
        BACKGROUND = -255,
        MIDDLEGROUND = 0,
        FOREGROUND = 255,

        HUD = 2048
    };

    void draw(std::pair<int, std::function<void(Renderer&)>>);

    void render();

    void setRenderer(sf::RenderTarget& renderer);

    void setView(sf::View const& view);
    const sf::View& getView() const;
    sf::IntRect getViewport(sf::View const& view) const;
    sf::Vector2u getSize() const;

    void draw(sf::Shape& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::Sprite const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::Text const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::VertexArray const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, sf::RenderStates const& states = sf::RenderStates::Default);

    void drawHUD(sf::CircleShape& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::RectangleShape& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::ConvexShape& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::Sprite const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::Text const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::VertexArray const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, sf::RenderStates const& states = sf::RenderStates::Default);

private:
    std::vector<std::pair<int, std::function<void(Renderer&)>>> m_drawCallbacks;

    bool isInScreen(sf::FloatRect const& rect) const;

    sf::RenderTarget* m_renderer;
    sf::IntRect m_screenRect;

};