//
// Created on 2021-08-08.
//

#include "particle_buoyancy.h"

#include <glm/vec3.hpp>

void ParticleBuoyancy::update_force(std::shared_ptr<Particle> p_particle, real p_duration)
{
    real depth = p_particle->get_position().y;

    // Check if we're out of the water.
    if (depth >= m_waterHeight + m_maxDepth) {
        return;
    }

    glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);

    // Check if we're at maximum depth.
    if (depth <= m_waterHeight - m_maxDepth)
    {
        force.y = m_liquidDensity * m_volume;
        p_particle->add_force(force);
        return;
    }

    // Otherwise we are partly submerged.
    force.y = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth;
    p_particle->add_force(force);
}
