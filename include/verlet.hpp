#pragma once
#include <vector>
#include "particle.hpp"

void verletStep(std::vector<particle2d>& P, const double dt, const double G);
void verletStepParallel(std::vector<particle2d>& P, const double dt, const double G);