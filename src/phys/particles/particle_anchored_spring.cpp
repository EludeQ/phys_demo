//
// Created on 2021-08-08.
//

#include "particle_anchored_spring.h"

#include <glm/glm.hpp>

#include <iostream>

void ParticleAnchoredSpring::update_force(std::shared_ptr<Particle> particle, real duration)
{
    glm::vec3 force = particle->get_position();
    force -= m_anchor;

    real magnitude = force.length();
    magnitude = (m_restLength - magnitude) * m_springConstant;

    force = glm::normalize(force);
    force *= magnitude;
    particle->add_force(force);
//    std::cout << force.x << "," << force.y << "," << force.z << std::endl;
}
