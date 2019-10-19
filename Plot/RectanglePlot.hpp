#pragma once
#include "LineShape.hpp"
#include <SFML/Graphics.hpp>
#include <list>
class RectanglePlot : public sf::Drawable, public sf::Transformable
{
private:
    sf::LineShape m_ZeroLine;
    sf::RectangleShape m_Outline;
    sf::CircleShape m_Point;
    std::list<float> m_Data;
    //std::vector<sf::LineShape> m_Lines;
    float m_fMax;
    float m_fStep;
    unsigned int m_uiMax;
    

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    RectanglePlot(sf::Vector2f p_Size,float p_fStep = 5.f);
    ~RectanglePlot();
    void Add(float p_fValue);
};
