//
// Created on 16/07/2021.
//

#include "particle_gravity.h"

#include <iostream>

#include "particle.h"

void ParticleGravity::update_force(std::shared_ptr<Particle> p_particle, real p_duration)
{
    if (!p_particle->has_finite_mass()) {
        return;
    }

    p_particle->add_force(gravity * p_particle->get_mass());
}
