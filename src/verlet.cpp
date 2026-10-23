#include "verlet.hpp"
#include "gravity.hpp"


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

void verletStepParallel(std::vector<particle2d>& P, const double dt, const double G)
{

    std::vector<vec2d> old_acc(P.size());
    
    for (int i=0;i<P.size();i++)
    {
        old_acc[i] = P[i].acc;

        P[i].pos = P[i].pos + P[i].vel*dt + P[i].acc*(dt*dt)*0.5;

    }

    computeAccelParallel(P, G);

    for (int i=0;i<P.size();i++)
    {

        P[i].vel = P[i].vel + (old_acc[i] + P[i].acc)*dt*0.5;

    }
    
}