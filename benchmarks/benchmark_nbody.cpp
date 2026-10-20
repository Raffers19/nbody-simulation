
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "particle.hpp"
#include "gravity.hpp"
#include "verlet.hpp"

int main(int argc, char* argv[])
{
    int N = 400;

    if (argc > 1)
    {
        N = std::stoi(argv[1]);
    }

    if (N <= 0)
    {
        std::cerr << "Particle count must be positive\n";
        return 1;
    }

    constexpr int steps = 100;
    constexpr double dt = 0.001;
    constexpr double G = 0.001;

    std::vector<particle2d> P(N);

    // Initialize particles on a regular grid
    const int width = static_cast<int>(std::ceil(std::sqrt(N)));
    
    for (int i = 0; i < N; ++i)
    {
        P[i].mass = 1.0;

        P[i].pos = {
            static_cast<double>(i % width),
            static_cast<double>(i / width)
        };

        P[i].vel = {0.0, 0.0};
    }

    // Calculate initial accelerations
    computeAccel(P, G);

    // Start timing
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < steps; ++i)
    {
        verletStep(P, dt, G);
    }

    // Stop timing
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Particles: " << N << '\n';
    std::cout << "Steps:     " << steps << '\n';
    std::cout << "Time:      " << elapsed.count()
              << " seconds\n";

    // Make the computed result observable
    std::cout << "Final position: "
              << P[0].pos.x << ", "
              << P[0].pos.y << '\n';

    return 0;
}
