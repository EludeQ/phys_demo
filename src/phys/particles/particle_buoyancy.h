//
// Created on 2021-08-08.
//

#pragma once

#include "particle_force_generator.h"

class ParticleBuoyancy : public ParticleForceGenerator
{
    // Maximum submersion depth of the object before it generates its maximum buoyancy force.
    real m_maxDepth;
    // Object's volume
    real m_volume;
    // Height of the water plane above y = 0; Parallel to the XZ plane.
    real m_waterHeight;
    // Density liquid, water's is 1000 KG/M3
    real m_liquidDensity;
public:
    ParticleBuoyancy(const real &p_maxDepth, const real &p_volume, const real &p_waterHeight, const real &p_liquidDensity = 1000.0f)
        : m_maxDepth(p_maxDepth), m_volume(p_volume), m_waterHeight(p_waterHeight), m_liquidDensity(p_liquidDensity) {}

    void update_force(std::shared_ptr<Particle> p_particle, real p_duration) override;
};

