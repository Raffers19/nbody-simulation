#pragma once
#include "particle.hpp"
#include "verlet.hpp"
#include "gravity.hpp"
#include <vector>


class Simulation
{
    private:
    double G;
    double dt;
    double time = 0.0;
    bool accelerationValid = false;
    std::vector<particle2d> particles{};


    public:
    Simulation(double gravity=1.0, double timestep=0.1)
        : G{gravity}, dt{timestep}
    {
    }

    void setTimestep(const double& new_time) 
    {
        dt = new_time;
    }

    double getTimestep() const
    {
        return dt;
    }

    void addParticle(const particle2d& p)
    {
        accelerationValid = false;
        particles.push_back(p);
    }

    std::size_t getParticleCount() const
    {
        return particles.size();
    }

    void step()
    {
        if(accelerationValid == false)
        {
            computeAccel(particles, G);
            accelerationValid = true;
        }
        verletStep(particles, dt, G);
        time += dt;
    }

    void resetTime()
    {
        time = 0.0;
    }

    double getTime() const
    {
        return time;
    }
};