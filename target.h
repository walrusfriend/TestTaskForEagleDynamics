#ifndef TARGET_H
#define TARGET_H

#include <iostream>

class Target
{
public:
    Target(double, double);

    double x;
    double z;
    double V;
    double psi;
    double n;

    double setNewRandomTimingToChangen(double dt);
    void setNewRandomn();
};

#endif // TARGET_H
