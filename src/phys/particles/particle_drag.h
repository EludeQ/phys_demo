//
// Created on 16/07/2021.
//

#pragma once

#include "force_generator.h"

class ParticleDrag : public ForceGenerator
{
    // Velocity Drag Coefficient.
    real k1;

    // Velocity squared drag coefficient.
    real k2;

public:
    ParticleDrag(const real p_k1, const real p_k2) : k1(p_k1), k2(p_k2) {}

    void update_force(std::shared_ptr<Particle> particle, real duration) override;
};

