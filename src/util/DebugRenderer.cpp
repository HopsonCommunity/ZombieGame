#include "DebugRenderer.h"

#include <iostream>


DebugRenderer::Options::Options(int frame, sf::Color const& color)
    : frame(frame), color(color) {}

DebugRenderer::ToDraw::ToDraw(Raycast const& r, DebugRenderer::Options const& options)
    : type(DebugRenderer::ToDraw::Type::Raycast), raycast(r), options(options) {}
DebugRenderer::ToDraw::ToDraw(sf::Text const& t, DebugRenderer::Options const& options)
    : type(DebugRenderer::ToDraw::Type::Text), text(t), options(options) {}
    
DebugRenderer::ToDraw& DebugRenderer::ToDraw::operator=(ToDraw const& t) {
    type = t.type;
    options = t.options;
    if (type == DebugRenderer::ToDraw::Type::Raycast) {
        raycast = t.raycast;
    } else {
        text = t.text;
    }
}

DebugRenderer::ToDraw::~ToDraw() {}
DebugRenderer::ToDraw::ToDraw(ToDraw const& t) {
    type = t.type;
    options = t.options;
    if (type == DebugRenderer::ToDraw::Type::Raycast) {
        raycast = t.raycast;
    } else {
        text = t.text;
    }
}

void DebugRenderer::drawRaycast(Raycast const& r, DebugRenderer::Options const& options) {
    toDraw.emplace_back(r, options);
}

void DebugRenderer::drawText(sf::Text const& t, DebugRenderer::Options const& options) {
    toDraw.emplace_back(t, options);
}

void DebugRenderer::draw(sf::RenderTarget& renderer) {
    for (auto& d : toDraw) {
        if (d.type == DebugRenderer::ToDraw::Type::Raycast) {
            sf::Vertex vs[2];
            vs[0].position = d.raycast.start;
            vs[0].color = d.options.color;
            vs[1].position = d.raycast.start + d.raycast.direction * d.raycast.distance;
            vs[1].color = d.options.color;
            renderer.draw(vs, 2, sf::PrimitiveType::Lines);
        } else if (d.type == DebugRenderer::ToDraw::Type::Text) {
            renderer.draw(d.text);
        }
        d.options.frame--;
    }
    toDraw.erase( std::remove_if(toDraw.begin(), toDraw.end(), [](auto const& d) {
        return d.options.frame < 0;
    }), toDraw.end() );
}
