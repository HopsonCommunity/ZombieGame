#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

using ZIndex_t = int;
struct ZIndex {
    static constexpr ZIndex_t BACKGROUND     = 0;
    static constexpr ZIndex_t MIDDLEGROUND   = 256;
    static constexpr ZIndex_t FOREGROUND     = 512;
    static constexpr ZIndex_t HUD            = 1024;
    static constexpr ZIndex_t DEBUG          = 2048;
};

class Renderer
{
public:

    Renderer(sf::RenderTarget& renderer);
    Renderer();

    void render();

    void setRenderer(sf::RenderTarget& renderer);

    void setView(sf::View const& view);
    const sf::View& getView() const;
    sf::IntRect getViewport(sf::View const& view) const;
    sf::Vector2u getSize() const;

    void draw(sf::Shape const& shape,           ZIndex_t zIndex = ZIndex::MIDDLEGROUND, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::Sprite const& shape,          ZIndex_t zIndex = ZIndex::MIDDLEGROUND, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::Text const& shape,            ZIndex_t zIndex = ZIndex::MIDDLEGROUND, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::VertexArray const& shape,     ZIndex_t zIndex = ZIndex::MIDDLEGROUND, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type,  
                                                ZIndex_t zIndex = ZIndex::MIDDLEGROUND, sf::RenderStates const& states = sf::RenderStates::Default);

    void drawHUD(sf::CircleShape const& shape,                                          sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::RectangleShape const& shape,                                       sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::ConvexShape const& shape,                                          sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::Sprite const& shape,                                               sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::Text const& shape,                                                 sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::VertexArray const& shape,                                          sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, 
                                                                                        sf::RenderStates const& states = sf::RenderStates::Default);

private:
    using DrawCallback_t = std::function<void(sf::RenderTarget&)>;
    std::vector<std::pair<ZIndex_t, DrawCallback_t>> m_drawCallbacks;

    bool isInScreen(sf::FloatRect const& rect) const;

    sf::RenderTarget* m_renderer;
    sf::IntRect m_screenRect;

};