
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <complex>
#include "Plot/LineShape.hpp"

class RoundChart : public sf::Drawable, public sf::Transformable
{
private:
    std::vector<sf::LineShape> m_Lines;
    std::vector<std::complex<float>> m_Positions;
    sf::CircleShape m_ZeroShape;
    sf::CircleShape m_ZeroShapeBackground;
    sf::CircleShape m_OneShape;
    sf::CircleShape m_Center;
    sf::CircleShape m_Point;
    float m_fRadius;
    size_t m_Size;
    float m_fSpan;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    RoundChart(float p_fRadius = 100.f, size_t p_Size = 1000);
    ~RoundChart();
    void Update(const std::vector<std::complex<float>> &p_vData, std::complex<float> center);
};
