//
// Created on 2021-08-08.
//

#pragma once

#include <utility>

#include "particle_force_generator.h"
#include "precision.h"

class ParticleSpring : public ParticleForceGenerator
{
    // Particle on the other end of the spring
    std::shared_ptr<Particle> m_other;

    real m_springConstant;
    real m_restLength;
public:
    ParticleSpring(std::shared_ptr<Particle> p_other, real p_springConstant, real p_restLength) : m_other(std::move(p_other)), m_springConstant(p_springConstant), m_restLength(p_restLength) {}
    void update_force(std::shared_ptr<Particle> p_particle, real p_duration) override;
};

