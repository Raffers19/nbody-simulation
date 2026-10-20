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