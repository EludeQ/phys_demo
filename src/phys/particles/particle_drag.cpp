//
// Created on 16/07/2021.
//

#include "particle_drag.h"

#include <glm/glm.hpp>

void ParticleDrag::update_force(std::shared_ptr<Particle> particle, real duration)
{
    glm::vec3 force = particle->get_velocity();

    // Calculate drag coefficient
    real drag_coeff = glm::length(force);
    drag_coeff = k1 * drag_coeff + k2 * drag_coeff * drag_coeff;

    // Calculate force and apply
    // Force may not be (0.0f, 0.0f, 0.0f) or else it'll become NaN during normalization!!!
    if (force != glm::vec3(0.0f, 0.0f, 0.0f))
    {
        force = glm::normalize(force);
        force *= -drag_coeff;
        particle->add_force(force);
    }
}
