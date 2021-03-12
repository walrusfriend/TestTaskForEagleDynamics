#include "interceptor.h"

Interceptor::Interceptor(double startVelocity) :
    x(0),
    z(0),
    V(startVelocity),
    n(1),
    nMax(30),
    m(230),
    mFuel(60),
    S(0.9),
    A(1.5),
    J(235),
    t_engine(6)
{
    // Fill the Cx0 map
    m_Cx0[0.5] = 0.012;
    m_Cx0[0.9] = 0.015;
    m_Cx0[1.2] = 0.046;
    m_Cx0[1.5] = 0.044;
    m_Cx0[2.0] = 0.038;
    m_Cx0[3.0] = 0.030;
    m_Cx0[4.0] = 0.026;

    mDry = m - mFuel;

    // Calculate the engine thrust
    dm = mFuel / t_engine;
    P = dm * J * g_g;

    // Mach number
    M = V / g_a;
}

double Interceptor::giveCx()
{
    // Find first element that greater than
    auto p_Cx0 = m_Cx0.upper_bound(M);
    if (p_Cx0 == m_Cx0.end()) {
        std::cerr << "Couldn't find Cx0." << std::endl;
        --p_Cx0;
        // Return biggest value
        return p_Cx0->second;
    }
    double Cx0 = p_Cx0->second;
    double Cy = 0.1;    // Stop gap
    double Cx = Cx0 + A * pow(Cy, 2);
    return Cx;
}
