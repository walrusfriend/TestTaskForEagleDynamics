#ifndef INTERCEPTOR_H
#define INTERCEPTOR_H

#include <iostream>

#include <map>
#include <QDebug>

extern const double g_g;
extern const double g_a;

class Interceptor
{
public:
    Interceptor(double);

    double x;
    double z;
    double V;                       // Velocity
    double psi;                     // Angle of yaw
    double n;                       // G load
    double nMax;                    // Max G load
    double m;                       // Mass of the interceptor
    double mFuel;                   // Mass of the fuel on interceptor
    double mDry;                    // Mass of the interceptor without fuel
    double P;                       // engine thrust
    double M;                       // Mach number
    double S;                       // reference area
    double dm;                      // Mass flux
    std::map<double, double> m_Cx0; // Drag component at zero lift

    double giveCx();

private:
    double A;                       // drag-due-to-lift factor
    double J;                       // Specific impulse
    double t_engine;                // Operating time of the propulsion system
};

#endif // INTERCEPTOR_H
