
#include <cmath>
#include <iostream>
#include <vector>

#include "particle.hpp"
#include "gravity.hpp"

int main()
{
    constexpr double G = 1.0;
    constexpr double tolerance = 1e-12;

    std::vector<particle2d> P(3);

    P[0].mass = 1.0;
    P[0].pos = {0.0, 0.0};

    P[1].mass = 2.0;
    P[1].pos = {1.0, 0.0};

    P[2].mass = 3.0;
    P[2].pos = {0.0, 2.0};

    computeAccel(P, G);

    vec2d totalForce{0.0, 0.0};

    for (const auto& p : P)
    {
        totalForce = totalForce + p.acc * p.mass;
    }

    const double error = totalForce.norm();

    std::cout << "Total force magnitude: "
              << error << '\n';

    if (!std::isfinite(error) || error > tolerance)
    {
        std::cerr << "Momentum consistency test failed\n";
        return 1;
    }

    return 0;
}
