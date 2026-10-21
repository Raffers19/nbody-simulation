
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

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

    const int width =
        static_cast<int>(std::ceil(std::sqrt(N)));

    for (int i = 0; i < N; ++i)
    {
        P[i].mass = 1.0;

        P[i].pos = {
            static_cast<double>(i % width),
            static_cast<double>(i / width)
        };

        P[i].vel = {0.0, 0.0};
    }

    computeAccel(P, G);

    // Independent copy for acceleration benchmarking
    std::vector<particle2d> forceParticles = P;

    using clock = std::chrono::steady_clock;

    // Benchmark computeAccel()
    double checksum = 0.0;

    auto forceStart = clock::now();

    for (int i = 0; i < steps; ++i)
    {
        computeAccel(forceParticles, G);
        checksum += forceParticles[0].acc.x;
    }

    auto forceEnd = clock::now();

    std::chrono::duration<double> forceTime =
        forceEnd - forceStart;

    // Benchmark complete velocity-Verlet steps
    auto verletStart = clock::now();

    for (int i = 0; i < steps; ++i)
    {
        verletStep(P, dt, G);
    }

    auto verletEnd = clock::now();

    std::chrono::duration<double> verletTime =
        verletEnd - verletStart;

    // Report results
    std::cout << "Particles: " << N << '\n';
    std::cout << "Steps: " << steps << '\n';

    std::cout << "Acceleration time: "
              << forceTime.count() << " seconds\n";

    std::cout << "Verlet time: "
              << verletTime.count() << " seconds\n";

    std::cout << "Time ratio: "
              << forceTime.count() / verletTime.count()
              << '\n';

    std::cout << "Checksum: " << checksum << '\n';

    std::cout << "Final position: "
              << P[0].pos.x << ", "
              << P[0].pos.y << '\n';

    return 0;
}
