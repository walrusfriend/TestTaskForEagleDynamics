#ifndef TARGET_H
#define TARGET_H

#include "main.h"

class Target
{
public:
    Target(double);

private:
    double m_x;
    double m_y;
    double m_velocity;
    int8_t m_maxGLoad;
    double Mach;
};

#endif // TARGET_H
