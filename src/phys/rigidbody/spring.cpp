//
// Created on 22/08/2021.
//

#include "spring.h"

void Spring::update_force(std::shared_ptr<RigidBody> p_body, real p_duration)
{
    glm::vec3 lws = p_body->to_global(m_connection_point);
    glm::vec3 ows = m_other->to_global(m_other_connection_point);

    glm::vec3 force = lws - ows;

    real magnitude = force.length();
    magnitude = abs(magnitude - m_rest_length);
    magnitude *= m_spring_constant;

    glm::normalize(force);
    force *= -magnitude;
    p_body->add_force_at_point(force, lws);
}
