//
// Created on 14/06/2021.
//

#pragma once

#include <memory>

#include "particle.h"

class ForceGenerator
{
public:
    // Calculate and update force applied to particle.
    virtual void update_force(std::shared_ptr<Particle> particle, real duration) = 0;
};

