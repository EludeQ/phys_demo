//
// Created on 22/08/2021.
//

#include "gravity.h"

#include "rigid_body.h"

void Gravity::update_force(std::shared_ptr<RigidBody> p_body, real p_duration)
{
    if (!p_body->has_finite_mass())
    {
        return;
    }

    p_body->add_force(m_gravity * p_body->get_mass());
}
