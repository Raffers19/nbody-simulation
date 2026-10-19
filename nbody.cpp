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

double getParticleSquaredDistance(const particle2d& p1, const particle2d& p2)
{

    vec2d d = p2.pos - p1.pos;
    double r2 = d.squaredLength();

    return r2;
}

vec2d computeForce(const particle2d& p1, const particle2d& p2, const double G)
{
    //const double G{6.6743e-11};

    vec2d d = p2.pos - p1.pos;

    double r2 = getParticleSquaredDistance(p1, p2);
    double r = std::sqrt(r2);

    vec2d F = (d*p1.mass*p2.mass*G)/(r2*r);

    return F;

}

void computeAccel(std::vector<particle2d>& P, const double G)
{
    for(int j=0; j<P.size(); j++)
    {

        vec2d full_f;

        for(int i=0; i<P.size(); i++)
        {
            if (i != j)
            {
                vec2d f = computeForce(P[j], P[i], G);
                full_f += f;

            }

        }
        P[j].acc = full_f/P[j].mass;
    }
}

void verletStep(std::vector<particle2d>& P, const double dt, const double G)
{

    std::vector<vec2d> old_acc(P.size());
    
    for (int i=0;i<P.size();i++)
    {
        old_acc[i] = P[i].acc;

        P[i].pos = P[i].pos + P[i].vel*dt + P[i].acc*(dt*dt)*0.5;

    }

    computeAccel(P, G);

    for (int i=0;i<P.size();i++)
    {

        P[i].vel = P[i].vel + (old_acc[i] + P[i].acc)*dt*0.5;

    }
    
}

double computeKinetic(const std::vector<particle2d>& P)
{
    double kin{0};

    for(int i=0; i<P.size(); i++)
    {

        kin += 0.5*P[i].mass*(P[i].vel.squaredLength());
    }

    return kin;
}

double computePotential(const std::vector<particle2d>& P, const double G)
{
    //const double G{6.6743e-11};

    double pot{0};

    for(int j=0; j<P.size(); j++)
    {
        for (std::size_t i = j + 1; i < P.size(); i++)
        {   
            
            //double r2 = getParticleSquaredDistance(P[j], P[i]);
            double r = std::sqrt(getParticleSquaredDistance(P[j], P[i]));

            pot +=  -(G*P[i].mass*P[j].mass)/r;
            
        }
    }
    return pot;
}

double computeEnergy(const std::vector<particle2d>& P, const double G)
{
    double K = computeKinetic(P);
    double U = computePotential(P, G);

    return K+U;
}

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


