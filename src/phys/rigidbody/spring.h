//
// Created on 22/08/2021.
//

#pragma once

#include <memory>

#include <glm/vec3.hpp>

#include "force_generator.h"
#include "rigid_body.h"

class Spring : public ForceGenerator
{
    // Point of connection in local coordinates.
    glm::vec3 m_connection_point;
    // Point of connection to other object in that object's local coordinates.
    glm::vec3 m_other_connection_point;

    // Body on the other end of the spring.
    std::shared_ptr<RigidBody> m_other;

    real m_spring_constant;
    real m_rest_length;

public:
    Spring(const glm::vec3 &p_local_connection_point, std::shared_ptr<RigidBody> p_other, const glm::vec3 &p_other_connection_point, real p_spring_constant, real p_rest_length)
        : m_connection_point(p_local_connection_point), m_other(p_other), m_other_connection_point(p_other_connection_point), m_spring_constant(p_spring_constant), m_rest_length(p_rest_length) {}

    void update_force(std::shared_ptr<RigidBody> p_body, real p_duration) override;
};

