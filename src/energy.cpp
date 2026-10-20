#include "energy.hpp"
#include "gravity.hpp"

double computeKinetic(const std::vector<particle2d>& P)
{
    double kin{0};

    for(int i=0; i<P.size(); i++)
    {

        kin += 0.5*P[i].mass*(P[i].vel.squaredLength());
    }

    return kin;
}

double computePotential(const std::vector<particle2d>& P, const double G)
{
    //const double G{6.6743e-11};

    double pot{0};

    for(int j=0; j<P.size(); j++)
    {
        for (std::size_t i = j + 1; i < P.size(); i++)
        {   
            
            double r = std::sqrt(getParticleSquaredDistance(P[j], P[i]));

            pot +=  -(G*P[i].mass*P[j].mass)/r;
            
        }
    }
    return pot;
}

double computeEnergy(const std::vector<particle2d>& P, const double G)
{
    double K = computeKinetic(P);
    double U = computePotential(P, G);

    return K+U;
}