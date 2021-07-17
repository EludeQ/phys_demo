//
// Created on 14/06/2021.
//

#pragma once

#include <vector>
#include <memory>

#include "force_generator.h"
#include "particle.h"

class ForceRegistry
{
protected:
    struct Registration
    {
        std::shared_ptr<Particle> particle;
        std::shared_ptr<ForceGenerator> generator;
    };

    std::vector<Registration> registry;
public:
    // Adds particle-forcegen pair.
    void add(const std::shared_ptr<Particle>& p_particle, const std::shared_ptr<ForceGenerator>& p_fg);

    // Removes particle-forcegen pair.
    void remove(const std::shared_ptr<Particle>& p_particle, const std::shared_ptr<ForceGenerator>& p_fg);

    // Clears particle-forcegen registery.
    void clear();

    // Calls all force generators to update their particles.
    void update_forces(real duration);
};

