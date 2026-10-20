#pragma once
#include <vector>
#include "particle.hpp"

double getParticleSquaredDistance(const particle2d& p1, const particle2d& p2);
vec2d computeForce(const particle2d& p1, const particle2d& p2, const double G);
void computeAccel(std::vector<particle2d>& P, const double G);