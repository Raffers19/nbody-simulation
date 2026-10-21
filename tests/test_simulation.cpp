#include <iostream>
#include "simulation.hpp"
#include "particle.hpp"

int main()
{
    Simulation sim;

    particle2d p1{};
    particle2d p2{};

    sim.addParticle(p1);
    sim.addParticle(p2);

    if(sim.getParticleCount() != 2)
    {
        std::cerr << "simulation test FAILED\n";
        return 1;
    }

    std::cout << "simulation test PASSED\n";
    return 0;

}