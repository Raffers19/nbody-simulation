#pragma once
#include <vector>
#include "particle.hpp"

double computeKinetic(const std::vector<particle2d>& P);
double computePotential(const std::vector<particle2d>& P, const double G);
double computeEnergy(const std::vector<particle2d>& P, const double G);