#include "solver.h"

Solver::Solver()
{

}

void Solver::integrationEuler(std::map<std::string, std::vector<double>> &output,
                              Interceptor &interceptor, Target &target)
{
    double dt = 0.01;   // Step of integration

    // Create buffers
    std::vector<double> i_psi;
    double tmp_m = interceptor.m;
    std::vector<double> t_psi;

    i_psi.push_back(interceptor.psi);
    t_psi.push_back(target.psi);

    double distance = sqrt(pow(target.x - interceptor.x, 2) + pow(target.z - interceptor.z, 2));

    do {
        // time
        output["t"].push_back(output["t"].back() + dt);

        // ================================
        // Interceptor trajectory equations
        double X = interceptor.giveCx() * g_rho * pow(interceptor.V, 2) / 2 * interceptor.S;
        double dV = (interceptor.P - X) / interceptor.m;
        double tmp_V = output["V"].back() + dV * dt;
        output["V"].push_back(tmp_V);

        // Dogleg method
        // Angle of sighting
        double phi = atan((output["z_target"].back() - output["z"].back()) /
                          (output["x_target"].back() - output["x"].back()));
        i_psi.push_back(phi);

        interceptor.m = tmp_m - interceptor.dm * dt;
        tmp_m = interceptor.m;

        if (interceptor.m <= interceptor.mDry)
            interceptor.P = 0;

        double tmp_x = output["x"].back() + interceptor.V * cos(phi) * dt;
        double tmp_z = output["z"].back() - interceptor.V * sin(phi) * dt;
        output["x"].push_back(tmp_x);
        output["z"].push_back(tmp_z);

        interceptor.V = tmp_V;
        interceptor.x = tmp_x;
        interceptor.z = tmp_z;

        // ===========================
        // Target trajectory equations
        double timeToChangen = target.setNewRandomTimingToChangen(dt);
        if (timeToChangen--) {
            timeToChangen = target.setNewRandomTimingToChangen(dt);
            target.setNewRandomn();
        }
        output["n_target"].push_back(target.n);

        output["V_target"].push_back(target.V);
        double tmp_psi = t_psi.back() - (target.n * g_g / target.V) * dt;
        // Through 2 pi
        if (abs(tmp_psi) > 2 * g_pi) {
            if (tmp_psi > 0)
                tmp_psi -= 2 * g_pi;
            else
                tmp_psi += 2 * g_pi;
        }
        t_psi.push_back(tmp_psi);

        tmp_x = output["x_target"].back() + target.V * cos(tmp_psi) * dt;
        tmp_z = output["z_target"].back() - target.V * sin(tmp_psi) * dt;
        output["x_target"].push_back(tmp_x);
        output["z_target"].push_back(tmp_z);

        target.x = tmp_x;
        target.z = tmp_z;


        distance = sqrt(pow(target.x - interceptor.x, 2) + pow(target.z - interceptor.z, 2));

        qDebug() << interceptor.V << target.V << distance;
    } while (interceptor.V > target.V && distance > 15);

}
