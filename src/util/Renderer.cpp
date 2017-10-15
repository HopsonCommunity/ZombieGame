#include "Renderer.h"

Renderer::Renderer(sf::RenderTarget& renderer)
:   renderer(&renderer),
    screenRect(renderer.getViewport(renderer.getView())) {}

Renderer::Renderer()
:   renderer(nullptr),
    screenRect(sf::IntRect(0, 0, 0, 0)) {}
    
void Renderer::setRenderer(sf::RenderTarget& renderer)
{
    this->renderer = &renderer;
}

void Renderer::setView(sf::View const& view)
{
    renderer->setView(view);
    screenRect = renderer->getViewport(view);
    auto center = view.getCenter();
    screenRect.left = center.x - screenRect.width / 2.f;
    screenRect.top = center.y - screenRect.height / 2.f;
}

const sf::View& Renderer::getView() const 
{
    return renderer->getView();
}

sf::IntRect Renderer::getViewport(sf::View const& view) const
{
    return renderer->getViewport(view);
}

sf::Vector2u Renderer::getSize() const
{
    return renderer->getSize();
}

bool Renderer::isInScreen(sf::FloatRect const& rect) const
{
    return !(   rect.left               > screenRect.left + screenRect.width
           ||   rect.left + rect.width  < screenRect.left
           ||   rect.top                > screenRect.top + screenRect.height
           ||   rect.top + rect.height  < screenRect.top
    );
}

void Renderer::draw(sf::Shape const& shape, sf::RenderStates const& states)
{
    auto bounds = shape.getGlobalBounds();
    if(isInScreen(bounds))
    {
        renderer->draw(shape, states);
    }
}

void Renderer::draw(sf::Sprite const& sprite, sf::RenderStates const& states)
{
    auto bounds = sprite.getGlobalBounds();
    if(isInScreen(bounds))
    {
        renderer->draw(sprite, states);
    }
}

void Renderer::draw(sf::Text const& text, sf::RenderStates const& states)
{
    auto bounds = text.getGlobalBounds();
    if(isInScreen(bounds))
    {
        renderer->draw(text, states);
    }
}

void Renderer::draw(sf::VertexArray const& vs, sf::RenderStates const& states)
{
    auto bounds = vs.getBounds();
    if(isInScreen(bounds))
    {
        renderer->draw(vs, states);
    }
}

void Renderer::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, sf::RenderStates const& states)
{
    sf::FloatRect rect(0, 0, 0, 0);
    for(unsigned int i = 0; i < vertexCount; ++i)
    {
        auto p = vertices[i].position;
        if (p.x < rect.left) rect.left = p.x;
        if (p.x > rect.width) rect.width = p.x;
        if (p.y < rect.top) rect.top = p.y;
        if (p.y > rect.height) rect.height = p.y;
    }
    rect.width -= rect.left;
    rect.height -= rect.top;

    if(isInScreen(rect))
    {
        renderer->draw(vertices, vertexCount, type, states);
    }
}

void Renderer::drawHUD(sf::CircleShape const& shape, sf::RenderStates const& states)
{
    sf::CircleShape s = shape;
    auto px = s.getPosition() / 100.f;
    auto pw = renderer->mapPixelToCoords({static_cast<int>(px.x * screenRect.width), static_cast<int>(px.y * screenRect.height)});
    s.setPosition(pw);
    renderer->draw(s, states);
}

void Renderer::drawHUD(sf::RectangleShape const& shape, sf::RenderStates const& states)
{
    sf::RectangleShape s = shape;
    auto px = s.getPosition() / 100.f;
    auto pw = renderer->mapPixelToCoords({static_cast<int>(px.x * screenRect.width), static_cast<int>(px.y * screenRect.height)});
    s.setPosition(pw);
    renderer->draw(s, states);
}

void Renderer::drawHUD(sf::ConvexShape const& shape, sf::RenderStates const& states)
{
    sf::ConvexShape s = shape;
    auto px = s.getPosition() / 100.f;
    auto pw = renderer->mapPixelToCoords({static_cast<int>(px.x * screenRect.width), static_cast<int>(px.y * screenRect.height)});
    s.setPosition(pw);
    renderer->draw(s, states);
}

void Renderer::drawHUD(sf::Sprite const& sprite, sf::RenderStates const& states)
{
    sf::Sprite s = sprite;
    auto px = s.getPosition() / 100.f;
    auto pw = renderer->mapPixelToCoords({static_cast<int>(px.x * screenRect.width), static_cast<int>(px.y * screenRect.height)});
    s.setPosition(pw);
    renderer->draw(s, states);
}

void Renderer::drawHUD(sf::Text const& text, sf::RenderStates const& states)
{
    sf::Text t = text;
    auto px = text.getPosition() / 100.f;
    auto pw = renderer->mapPixelToCoords({static_cast<int>(px.x * screenRect.width), static_cast<int>(px.y * screenRect.height)});
    t.setPosition(pw);
    renderer->draw(t, states);
}

void Renderer::drawHUD(sf::VertexArray const& vs, sf::RenderStates const& states)
{
    sf::VertexArray v = vs;
    for (unsigned int i = 0; i < vs.getVertexCount(); ++i)
    {
        auto px = vs[i].position / 100.f;
        auto pw = renderer->mapPixelToCoords({static_cast<int>(px.x * screenRect.width), static_cast<int>(px.y * screenRect.height)});
        v[i].position = pw;
    }
    renderer->draw(v, states);
}

void Renderer::drawHUD(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, sf::RenderStates const& states)
{
    auto vs = new sf::Vertex[vertexCount];
    for (unsigned int i = 0; i < vertexCount; ++i)
    {
        auto px = vertices[i].position / 100.f;
        auto pw = renderer->mapPixelToCoords({static_cast<int>(px.x * screenRect.width), static_cast<int>(px.y * screenRect.height)});
        vs[i].position = pw;
    }

    renderer->draw(vs, vertexCount, type, states);
    delete [] vs;
}
