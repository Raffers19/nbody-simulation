
#include <iostream>
#include <cmath>
#include <vector>

#include "particle.hpp"
#include "gravity.hpp"
#include "verlet.hpp"

double positionError(double dt, int steps)
{
    std::vector<particle2d> P(2);

    const double G = 1.0;

    P[0].mass = 1.0;
    P[0].pos = {0.5, 0.0};
    P[0].vel = {0.0, 1.0 / std::sqrt(2.0)};

    P[1].mass = 1.0;
    P[1].pos = {-0.5, 0.0};
    P[1].vel = {0.0, -1.0 / std::sqrt(2.0)};

    computeAccel(P, G);

    for (int i = 0; i < steps; ++i)
    {
        verletStep(P, dt, G);
    }

    const double T = dt * steps;

    vec2d exact{
        0.5 * std::cos(std::sqrt(2.0) * T),
        0.5 * std::sin(std::sqrt(2.0) * T)
    };

    return (P[0].pos - exact).norm();
}

int main()
{
    const double T = 5.0;

    const int steps1 = 100;
    const int steps2 = 200;

    const double dt1 = T / steps1;
    const double dt2 = T / steps2;

    const double error1 = positionError(dt1, steps1);
    const double error2 = positionError(dt2, steps2);

    const double order = std::log2(error1 / error2);

    std::cout << "Coarse error: " << error1 << '\n';
    std::cout << "Fine error:   " << error2 << '\n';
    std::cout << "Order:        " << order << '\n';

    if (!std::isfinite(order) ||
        std::abs(order - 2.0) > 0.05)
    {
        std::cerr << "Verlet convergence FAILED\n";
        return 1;
    }

    std::cout << "Verlet convergence PASSED\n";
    return 0;
}
