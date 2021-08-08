//
// Created on 2021-08-08.
//

#pragma once

#include "force_generator.h"

class ParticleAnchoredSpring : public ForceGenerator
{
protected:
    glm::vec3 m_anchor;
    real m_springConstant;
    real m_restLength;
public:
    ParticleAnchoredSpring(const glm::vec3& p_anchor, real p_springConstant, real p_restLength) : m_anchor(p_anchor), m_springConstant(p_springConstant), m_restLength(p_restLength) {}

    void update_force(std::shared_ptr<Particle> particle, real duration) override;
};

