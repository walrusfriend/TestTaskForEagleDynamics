#ifndef SOLVER_H
#define SOLVER_H

#include <cmath>

#include "interceptor.h"
#include "target.h"

extern const double g_rho;
extern const double g_pi;

class Solver
{
public:
    Solver();

    void integrationEuler(std::map<std::string, std::vector<double>> &output,
                          Interceptor &interceptor, Target &target);
};

#endif // SOLVER_H
