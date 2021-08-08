//
// Created on 14/06/2021.
//

#pragma once

#include <memory>

#include "particle.h"

class ParticleForceGenerator
{
public:
    // Calculate and update force applied to p_particle.
    virtual void update_force(std::shared_ptr<Particle> p_particle, real p_duration) = 0;
};

