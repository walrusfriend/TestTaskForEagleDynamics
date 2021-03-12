#include "target.h"

Target::Target(double startVelocity, double distance) :
    x(distance),
    z(0),
    V(startVelocity)
{
    setNewRandomn();
}

double Target::setNewRandomTimingToChangen(double dt)
{
    return (rand() % 60) * dt; // 360 - time of engine thrust;
}

void Target::setNewRandomn()
{
    n = rand() % 19 - 9;
}
