//
// Created on 21/08/2021.
//

#include "rigid_body.h"

static inline void transform_inertia_tensor(glm::mat3 &p_iitWorld, const glm::mat3 p_iitBody, const glm::mat4 &p_transform)
{
    p_iitWorld[0] = p_transform[0];
    p_iitWorld[1] = p_transform[1];
    p_iitWorld[2] = p_transform[2];
    p_iitWorld *= p_iitBody;
}

static inline void calculate_transform_matrix(glm::mat4 &p_transform_matrix, const glm::vec3 &p_position, const glm::quat &p_orientation) 
{
    p_transform_matrix = glm::translate(glm::identity<glm::mat4>(), p_position) * glm::mat4_cast(p_orientation);
}

void RigidBody::calculate_derived_data()
{
    m_orientation = glm::normalize(m_orientation);
    calculate_transform_matrix(m_transformMatrix, m_position, m_orientation);
    transform_inertia_tensor(m_inverseInertiaTensorWorld, m_inverseInertiaTensor, m_transformMatrix);
}

void RigidBody::set_inertia_tensor(const glm::mat3 &p_tensor)
{
    m_inverseInertiaTensor = glm::inverse(p_tensor);
}

void RigidBody::add_force(const glm::vec3 &p_force)
{
    m_forceAccum += p_force;
    m_isAwake = true;
}

void RigidBody::clear_accumulators()
{
    m_forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
    m_torqueAccum = glm::vec3(0.0f, 0.0f, 0.0f);
}

void RigidBody::integrate(real p_duration)
{
    m_lastFrameAcceleration = m_acceleration;
    m_lastFrameAcceleration += m_forceAccum * m_inverseMass;

    glm::vec3 angularAcceleration = m_torqueAccum * m_inverseInertiaTensorWorld;

    m_velocity += m_lastFrameAcceleration * p_duration;
    m_rotation += angularAcceleration * p_duration;

    m_velocity *= pow(m_linearDamping, p_duration);
    m_rotation *= pow(m_angularDamping, p_duration);

    m_position += m_velocity * p_duration;

    m_orientation += glm::quat(m_rotation * p_duration);

    calculate_derived_data();
    clear_accumulators();
}

void RigidBody::add_force_at_point(const glm::vec3 &p_force, const glm::vec3 &p_point)
{
    glm::vec3 pt = p_point;
    pt -= m_position;
    m_forceAccum += p_force;
    m_torqueAccum += glm::cross(pt, p_force);

    m_isAwake = true;
}

void RigidBody::add_force_at_body_point(const glm::vec3 &p_force, const glm::vec3 &p_point)
{
    // Convert p_point from local to global space.
    glm::vec3 pt = glm::vec4(p_point, 0.0f) * m_transformMatrix;
    add_force_at_point(p_force, pt);
    m_isAwake = true;
}

void RigidBody::set_mass(const real &p_mass)
{
    m_inverseMass = 1.0f / p_mass;
}

glm::vec3 RigidBody::to_global(glm::vec3 p_point)
{
    glm::vec4 point = glm::vec4(p_point, 1.0f);
    glm::vec4 transformed = m_transformMatrix * point;
    return glm::vec3(transformed);
}

void RigidBody::set_damping(const real &p_linearDamping, const real &p_angularDamping)
{
    m_linearDamping = p_linearDamping;
    m_angularDamping = p_angularDamping;
}
