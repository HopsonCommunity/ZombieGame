#pragma once

#include <SFML/Graphics.hpp>

class Renderer
{
public:

    Renderer(sf::RenderTarget& renderer);
    Renderer();
    
    void setRenderer(sf::RenderTarget& renderer);

    void setView(sf::View const& view);
    const sf::View& getView() const;
    sf::IntRect getViewport(sf::View const& view) const;
    sf::Vector2u getSize() const;

    void draw(sf::Shape const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::Sprite const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::Text const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(sf::VertexArray const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, sf::RenderStates const& states = sf::RenderStates::Default);

    void drawHUD(sf::CircleShape const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::RectangleShape const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::ConvexShape const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::Sprite const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::Text const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(sf::VertexArray const& shape, sf::RenderStates const& states = sf::RenderStates::Default);
    void drawHUD(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, sf::RenderStates const& states = sf::RenderStates::Default);

private:

    bool isInScreen(sf::FloatRect const& rect) const;

    sf::RenderTarget* renderer;
    sf::IntRect screenRect;

};