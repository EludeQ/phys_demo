//
// Created on 09/06/2021.
//

#pragma once

#include "glm/vec3.hpp"
#include "../precision.h"

class Particle
{
protected:
    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 m_acceleration{0.0f, 0.0f, 0.0f};
    glm::vec3 m_force_accum{0.0f, 0.0f, 0.0f}; // Accumulated force, is cleared at integration step.

    real m_damping;
    // We use the inverse of mass (1 / mass) so that we can have an infinite mass (0), since
    // a normal mass of 0 doesn't make sense anyway.
    real m_inverseMass;

    void clear_accumulator();

public:
    void integrate(float p_duration);

    glm::vec3 get_position() { return m_position; }

    glm::vec3 get_velocity() { return m_velocity; }
    glm::vec3 get_acceleration() { return m_acceleration; }
    real get_damping() const { return m_damping; }
    real get_inverse_mass() const { return m_inverseMass; }
    real get_mass() const { return (1.0f / m_inverseMass); }
    bool has_finite_mass() const { return m_inverseMass > 0.0f; };

    void set_velocity(const glm::vec3& p_velocity);
    void set_acceleration(const glm::vec3& p_acceleration);
    void set_damping(const real& p_damping);
    void set_mass(const real& p_mass);
    void set_inverse_mass(const real& p_inverseMass);
    void set_position(const glm::vec3& p_position);

    // Adds force to particle. Is only applied at the next iteration.
    void add_force(const glm::vec3& p_force);
};

