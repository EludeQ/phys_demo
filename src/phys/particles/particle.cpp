//
// Created on 09/06/2021.
//

#include "particle.h"

#include <cmath>
#include <iostream>

#include "raylib.h"

void Particle::integrate(real p_duration)
{
    if (!has_finite_mass())
    {
        return;
    }

    assert(p_duration > 0.0);

    m_position = m_position + m_velocity * p_duration;

    glm::vec3 resulting_acc = m_acceleration;
    resulting_acc += m_force_accum * m_inverseMass;

    m_velocity += m_force_accum * m_inverseMass * p_duration;// resulting_acc * p_duration;
//    m_velocity *= pow(m_damping, p_duration);

    clear_accumulator();
}

void Particle::set_velocity(const glm::vec3& p_velocity)
{
    m_velocity = p_velocity;
}

void Particle::set_acceleration(const glm::vec3& p_acceleration)
{
    m_acceleration = p_acceleration;
}

void Particle::set_damping(const real& p_damping)
{
    m_damping = p_damping;
}

void Particle::set_inverse_mass(const real& p_inverseMass)
{
    m_inverseMass = p_inverseMass;
}

void Particle::set_mass(const real& p_mass)
{
    m_inverseMass = 1.0f / p_mass;
}

void Particle::clear_accumulator()
{
    m_force_accum = {0.0f, 0.0f, 0.0f};
}

void Particle::add_force(const glm::vec3 &p_force)
{
    m_force_accum += p_force;
}

void Particle::set_position(const glm::vec3 &p_position)
{
    m_position = p_position;
}
