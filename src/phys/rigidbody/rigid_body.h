//
// Created on 21/08/2021.
//

#pragma once

#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "../precision.h"

class RigidBody
{
protected:
    // We use the inverse of mass (1 / mass) so that we can have an infinite mass (0), since
    // a normal mass of 0 doesn't make sense anyway.
    real m_inverseMass;
    // Amount of damping - Required to remove energy.
    real m_linearDamping;
    real m_angularDamping;
    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::quat m_orientation = glm::identity<glm::quat>();
    glm::vec3 m_velocity{0.0f, 0.0f, 0.0f};
    glm::vec3 m_acceleration{0.0f, 0.0f, 0.0f};
    glm::vec3 m_lastFrameAcceleration{0.0f, 0.0f, 0.0f};
    glm::vec3 m_forceAccum{0.0f, 0.0f, 0.0f};
    glm::vec3 m_torqueAccum{0.0f, 0.0f, 0.0f};
    // Rotation is the angular velocity - Not the orientation.
    glm::vec3 m_rotation{0.0f, 0.0f, 0.0f};
    // Inverse inertia tensor in body coordinates.
    glm::mat3 m_inverseInertiaTensor;
    // And the same in world coordinates.
    glm::mat3 m_inverseInertiaTensorWorld;
    glm::mat4 m_transformMatrix;
    bool m_isAwake = false;
public:
    // Adds force (in world coordinates) to center of mass of the object.
    void add_force(const glm::vec3 &p_force);
    // Adds force to given point. Both are given in world coordinates. May generate rotation.
    void add_force_at_point(const glm::vec3 &p_force, const glm::vec3 &p_point);
    // Adds force (in world coordinates) to given point given in body space.
    void add_force_at_body_point(const glm::vec3 &p_force, const glm::vec3 &p_point);
    void integrate(real p_duration);
    void clear_accumulators();
    void calculate_derived_data();

    bool has_finite_mass() const { return m_inverseMass > 0.0f; };
    // Returns the global position of a point local to this object.
    glm::vec3 to_global(glm::vec3 p_point);

    real get_inverse_mass() const { return m_inverseMass; }
    real get_mass() const { return (1.0f / m_inverseMass); }
    glm::vec3 get_position() const { return m_position; }
    glm::quat get_orientation() const { return m_orientation; };

    void set_inverse_mass(const real& p_inverse_mass) { m_inverseMass = p_inverse_mass;};
    void set_mass(const real& p_mass);
    void set_damping(const real& p_linearDamping, const real& p_angularDamping);
    void set_inertia_tensor(const glm::mat3 &p_tensor);
    void set_position(const glm::vec3& p_pos) { m_position = p_pos; }
};

