// Experimental branch: testing alternative implementations
// Two-body gravitational orbit simulation
// Numerical integration of Newton's equations of motion
// Integration timestep is configurable

#include <iostream>
#include <numbers>
#include <cmath>
#include <vector>
#include <random>
#include "vec2d.hpp"
#include "particle.hpp"
#include "gravity.hpp"
#include "verlet.hpp"
#include "energy.hpp"

int main()
{
    std::vector<particle2d> P(2);

    const double G{1};
    
    std::vector<vec2d> init(5);

    init[0].x = 0.1;
    init[0].y = 50;
    init[1].x = 0.05;
    init[1].y = 100;
    init[2].x = 0.025;
    init[2].y = 200;
    init[3].x = 0.0125;
    init[3].y = 400;
    init[4].x = 0.00625;
    init[4].y = 800;

     
    std::vector<double> pos_error(init.size());

    for(int n=0; n<init.size(); n++)
    {
        P[0].mass = 1;
        P[0].pos.x = 0.5;
        P[0].pos.y = 0.0;
        P[0].vel.x = 0;
        P[0].vel.y = (1/std::sqrt(2));

        P[1].mass = 1;
        P[1].pos.x = -0.5;
        P[1].pos.y = 0.0;
        P[1].vel.x = 0;
        P[1].vel.y = -(1/std::sqrt(2));

        double dt = init[n].x;
        int step = init[n].y;

        computeAccel(P, G);

        double E0 = computeEnergy(P, G);
        
        for(int j=0; j<step; j++)
        {
            verletStep(P, dt, G);
        }

        double E1 = computeEnergy(P, G);

        //exact trajectory
        double T = dt*step;

        vec2d traj;
        traj.x = 0.5*std::cos(std::sqrt(2.0)*T);
        traj.y = 0.5*std::sin(std::sqrt(2.0)*T);

        double dx = P[0].pos.x - traj.x;
        double dy = P[0].pos.y - traj.y;

        pos_error[n] = std::sqrt(dx*dx + dy*dy);
    }

    for(int n=1; n<init.size(); n++)
    {
        std::cout << "error: " << std::log2(pos_error[n-1]/pos_error[n]) << '\n';
    }



    /*std::cout.precision(16);

    std::cout << "Initial energy: " << E0 << '\n';
    std::cout << "Final energy:   " << E1 << '\n';
    std::cout << "Relative error: "<< (E1 - E0) / std::abs(E0) << '\n';
    std::cout << "Position error: " << pos_error << '\n';*/

    return 0;
}


