#include "gravity.hpp"
#include <cmath>

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
    const std::size_t N = P.size();

    // Precompute inverse masses
    std::vector<double> invMass(N);

    for (std::size_t i = 0; i < N; ++i)
    {
        invMass[i] = 1.0 / P[i].mass;
        P[i].acc = {0.0, 0.0};
    }

    // Calculate each pair once
    for (std::size_t i = 0; i < N; ++i)
    {
        for (std::size_t j = i + 1; j < N; ++j)
        {
            const vec2d F = computeForce(P[i], P[j], G);

            P[i].acc = P[i].acc + F * invMass[i];
            P[j].acc = P[j].acc - F * invMass[j];
        }
    }
}
