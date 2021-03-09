#ifndef ROCKET_H
#define ROCKET_H

#include "main.h"

class Rocket
{
public:
    Rocket(double);

    double m_x;
    double m_y;
    double m_velocity;
    double m_Gload;
    double m_maxGLoad;
    double m_mass;
    double m_fuelMass;
    double m_specificImpulse;
    double m_timeEngineWork;        // operating time of the propulsion system
    double m_massFlux;
    double m_Mach;
    double m_S;                     // reference area
    std::map<double, double> m_Cx0;
};

#endif // ROCKET_H
