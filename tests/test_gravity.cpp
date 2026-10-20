
#include <iostream>
#include <cmath>
#include "gravity.hpp"

int main()
{
    particle2d p1{};
    particle2d p2{};

    p1.mass = 2.0;
    p1.pos = {0.0, 0.0};

    p2.mass = 3.0;
    p2.pos = {2.0, 0.0};

    const double G = 1.0;

    vec2d F = computeForce(p1, p2, G);

    const double tolerance = 1e-12;

    if (std::abs(F.x - 1.5) > tolerance ||
        std::abs(F.y) > tolerance)
    {
        std::cerr << "Gravity test FAILED\n";
        return 1;
    }

    std::cout << "Gravity test PASSED\n";
    return 0;
}
