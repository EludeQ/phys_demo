//
// Created on 2021-08-08.
//

#include "particle_spring.h"

#include <glm/glm.hpp>

void ParticleSpring::update_force(std::shared_ptr<Particle> p_particle, real p_duration)
{
    // Calculate spring vector
    glm::vec3 force = p_particle->get_position();
    force -= m_other->get_position();

    // Calculate force magnitude
    real magnitude = force.length();
    magnitude = abs(magnitude - m_restLength);
    magnitude *= m_springConstant;

    // Calculate final force and apply it.
    force = glm::normalize(force);
    force *= -magnitude;
    p_particle->add_force(force);
}
