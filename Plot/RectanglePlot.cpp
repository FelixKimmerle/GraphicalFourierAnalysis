#include "RectanglePlot.hpp"

RectanglePlot::RectanglePlot(sf::Vector2f p_Size, float p_fStep) : m_ZeroLine(sf::Vector2f(0, p_Size.y / 2),
                                                                              sf::Vector2f(p_Size.x, p_Size.y / 2)),
                                                                   m_Outline(p_Size),
                                                                   m_Point(1),
                                                                   m_fMax(0.f),
                                                                   m_fStep(p_fStep)

{
    m_ZeroLine.setThickness(1);
    m_ZeroLine.setFillColor(sf::Color(128, 128, 128));

    m_Outline.setOutlineThickness(1);
    m_Outline.setOutlineColor(sf::Color::Magenta);
    m_Outline.setFillColor(sf::Color::Transparent);

    m_Point.setOrigin(1, 1);

    m_uiMax = p_Size.x / p_fStep;
}

RectanglePlot::~RectanglePlot()
{
}

void RectanglePlot::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_ZeroLine, states);

    unsigned int c = 0;
    sf::Vector2f lastpos;
    sf::Vertex line[2];
    for (auto &&point : m_Data)
    {
        sf::RenderStates state = states;
        sf::Vector2f pos = sf::Vector2f(c * m_fStep, (point / (m_fMax * 2)) * m_Outline.getSize().y + m_Outline.getSize().y / 2);
        state.transform.translate(pos);
        target.draw(m_Point, state);
        if (c != 0)
        {
            line[0].position = lastpos;
            line[1].position = pos;
            line[0].color = sf::Color::Green;
            line[1].color = sf::Color::Green;
            target.draw(line, 2, sf::Lines, states);
        }
        lastpos = pos;
        c++;
    }
    target.draw(m_Outline, states);
}

void RectanglePlot::Add(float p_fValue)
{
    if (m_Data.size() >= m_uiMax)
    {
        m_Data.pop_front();
    }
    m_Data.push_back(p_fValue);
    if (std::abs(p_fValue) > m_fMax)
    {
        m_fMax = std::abs(p_fValue);
    }
}