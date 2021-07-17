//
// Created on 16/07/2021.
//

#include "particle_gravity.h"

#include <iostream>

#include "particle.h"

void ParticleGravity::update_force(std::shared_ptr<Particle> particle, real duration)
{
    if (!particle->has_finite_mass()) {
        return;
    }

    particle->add_force(gravity * particle->get_mass());
}
