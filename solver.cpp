#include "solver.h"

Solver::Solver()
{

}

void Solver::integrationEuler(std::map<std::string, std::vector<double>> &output,
                              Interceptor &interceptor, Target &target)
{
    double dt = 0.01;   // Step of integration

    // set time for next n_target change
    double timeToChangen = target.setNewRandomTimingToChangen(dt);

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
        // Define the coordinate quarter
        double dz = output["z_target"].back() - output["z"].back();
        double dx = output["x_target"].back() - output["x"].back();

        double phi;
        if (dz >= 0 && dx >= 0) {           // first quarter
            phi = -atan(dz / dx);
        } else if (dz > 0 && dx < 0) {      // second quarter
            phi = g_pi - atan(dz / dx);
        } else if (dz <= 0 && dx <= 0) {    // third quarter
            phi = -g_pi - atan(dz / dx);
        } else if (dz < 0 && dx > 0) {      // fourth quater
            phi = -atan(dz / dx);
        }

        // Define the limit angle of yaw for this G load
        double dpsi = (phi - i_psi.back()) / dt; // maybe (...)/dt
        if (abs(dpsi) > 2 * g_pi) {
            if (dpsi > 0)
                dpsi -= 2 * g_pi;
            else
                dpsi += 2 * g_pi;
        }

        double maxdPsi = g_g * interceptor.nMax / interceptor.V;
        if (maxdPsi > 2 * g_pi) {
            maxdPsi -= 2 * g_pi * (int)(maxdPsi / (2 * g_pi));
        }
        if (abs(dpsi) > maxdPsi) {
            if (dpsi < 0)
                dpsi = -maxdPsi;
            else
                dpsi = maxdPsi;
        }
        output["n"].push_back(-interceptor.V * dpsi/ g_g);

        interceptor.m = tmp_m - interceptor.dm * dt;
        tmp_m = interceptor.m;

        if (interceptor.m <= interceptor.mDry)
            interceptor.P = 0;

        double tmp_x = output["x"].back() + interceptor.V * cos(i_psi.back()) * dt;
        double tmp_z = output["z"].back() - interceptor.V * sin(i_psi.back()) * dt;
        output["x"].push_back(tmp_x);
        output["z"].push_back(tmp_z);

        i_psi.push_back(i_psi.back() + dpsi * dt);
        interceptor.V = tmp_V;
        interceptor.x = tmp_x;
        interceptor.z = tmp_z;

        // ===========================
        // Target trajectory equations
        if ((timeToChangen -= dt) <= 0) {
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
        output["distance"].push_back(distance);

        qDebug() << phi << dpsi << distance;
    } while (interceptor.V > target.V && distance > 15);

}
