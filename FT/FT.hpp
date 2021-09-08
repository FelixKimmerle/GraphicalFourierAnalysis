#pragma once
#include <vector>
#include <complex>

class FT
{
private:
    std::vector<float> m_Data;
    std::vector<std::complex<float>> m_Positions;
    std::vector<std::complex<float>> m_Centers;
    float m_fSpan;
public:
    FT(const std::vector<float> &p_Data);
    std::complex<float> Update(float p_fStep);
    std::vector<std::complex<float>> &GetData();

};
