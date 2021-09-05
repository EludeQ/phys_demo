//
// Created on 22/08/2021.
//

#pragma once

#include <glm/vec3.hpp>

#include "force_generator.h"

class Gravity : public ForceGenerator
{
protected:
    glm::vec3 m_gravity;
public:
    Gravity(const glm::vec3 &p_gravity) : m_gravity(p_gravity) {}

    void update_force(std::shared_ptr<RigidBody> p_body, real p_duration) override;
};

