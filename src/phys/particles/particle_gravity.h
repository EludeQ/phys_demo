//
// Created on 16/07/2021.
//

#pragma once

#include <glm/vec3.hpp>

#include "particle_force_generator.h"

class ParticleGravity : public ParticleForceGenerator
{
    glm::vec3 gravity;

public:
    ParticleGravity(const glm::vec3 &p_gravity) : gravity(p_gravity) {}

    void update_force(std::shared_ptr<Particle> particle, real duration) override;
};

