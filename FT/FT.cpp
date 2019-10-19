#include "FT.hpp"
#include <iostream>
FT::FT(const std::vector<float> &p_Data) : m_Data(p_Data),
                                           m_Positions(p_Data.size()),
                                           m_fSpan(1.f)
{
    float fMax = 0;
    for (auto &&i : m_Data)
    {
        if(std::abs(i) > fMax)
        {
            fMax = std::abs(i);
        }
    }
    fMax *= 2;
    for (auto &&i : m_Data)
    {
        i /= fMax;
        i += 0.5;
    }
    
    
}

FT::~FT()
{
}

std::complex<float> FT::Update(float p_fStep)
{
    m_fSpan += p_fStep;
    std::cout << m_fSpan << std::endl;
    unsigned int c = 0;
    std::complex<float> sum(0, 0);
    float fact = (1.f / m_Data.size()) * m_fSpan * 2.0 * M_PI;
    for (auto &&i : m_Data)
    {
        std::complex<float> point(i * std::sin((c + 1) * fact),
                                  i * std::cos((c + 1) * fact));
        m_Positions[c] = point;
        sum += point;
        c++;
    }
    sum /= m_Positions.size();
    m_Centers.push_back(sum);
    return sum;
}

std::vector<std::complex<float>> &FT::GetData()
{
    return m_Positions;
}