#include "RoundChart.hpp"
#include <cmath>
#include <iostream>
RoundChart::RoundChart(float p_fRadius, size_t p_Size) : m_ZeroShape(p_fRadius / 2 + 1, 100),
                                                                       m_ZeroShapeBackground(p_fRadius / 2 + 1, 100),
                                                                       m_OneShape(p_fRadius + 1, 100), m_fRadius(p_fRadius),
                                                                       m_Size(p_Size),
                                                                       m_fSpan(1.f)
{
    m_OneShape.setOutlineThickness(-2);
    m_OneShape.setOutlineColor(sf::Color::White);
    m_OneShape.setPosition(-p_fRadius - 1, -p_fRadius - 1);
    m_OneShape.setFillColor(sf::Color(0, 255, 0, 20));

    m_ZeroShape.setOutlineThickness(-2);
    m_ZeroShape.setOutlineColor(sf::Color::White);
    m_ZeroShape.setPosition(p_fRadius / 2 - p_fRadius - 1, p_fRadius / 2 - p_fRadius - 1);
    m_ZeroShape.setFillColor(sf::Color(0, 0, 255, 20));

    m_ZeroShapeBackground.setPosition(p_fRadius / 2 - p_fRadius - 1, p_fRadius / 2 - p_fRadius - 1);
    m_ZeroShapeBackground.setFillColor(sf::Color::Black);

    m_Center.setRadius(p_fRadius/50.f);
    m_Center.setFillColor(sf::Color::Cyan);
    m_Center.setOrigin(m_Center.getRadius(), m_Center.getRadius());

    m_Lines.reserve(p_Size);
    m_Positions.reserve(p_Size);

    m_Point.setFillColor(sf::Color::Red);
    m_Point.setRadius(p_fRadius/300.f);
    m_Point.setOrigin(p_fRadius/300.f, p_fRadius/300.f);
}

RoundChart::~RoundChart()
{
}
void RoundChart::Update(const std::vector<std::complex<float>> &p_vData, std::complex<float> center)
{
    m_Positions = p_vData;
    m_Lines.clear();

    for (auto i = p_vData.begin() + 1; i != p_vData.end(); i++)
    {

        sf::LineShape line(sf::Vector2f((i - 1)->real() * m_fRadius, (i - 1)->imag() * m_fRadius), sf::Vector2f(i->real() * m_fRadius, i->imag() * m_fRadius));
        line.setThickness(1);
        line.setFillColor(sf::Color::Yellow);
        m_Lines.push_back(line);
    }
    m_Center.setPosition(center.real() * m_fRadius, center.imag() * m_fRadius);
}
void RoundChart::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_OneShape, states);
    target.draw(m_ZeroShapeBackground, states);
    target.draw(m_ZeroShape, states);

    for (auto &&line : m_Lines)
    {
        target.draw(line, states);
    }
    for (auto &&point : m_Positions)
    {
        sf::RenderStates state = states;
        state.transform.translate(point.real() * m_fRadius, point.imag() * m_fRadius);
        target.draw(m_Point, state);
    }
    target.draw(m_Center, states);
}
