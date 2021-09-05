//
// Created on 22/08/2021.
//

#include "force_registry.h"

void ForceRegistry::add(const std::shared_ptr<RigidBody>& p_body, const std::shared_ptr<ForceGenerator>& p_fg)
{
    Registration registration;
    registration.body = p_body;
    registration.generator = p_fg;

    registry.push_back(registration);
}

void ForceRegistry::remove(const std::shared_ptr<RigidBody>& p_body, const std::shared_ptr<ForceGenerator>& p_fg)
{
    for (auto it = registry.begin(); it != registry.end(); ++it)
    {
        if (it->body == p_body && it->generator == p_fg)
        {
            registry.erase(it);
        }
    }
}

void ForceRegistry::update_forces(real duration)
{
    for (auto it = registry.begin(); it != registry.end(); ++it)
    {
        it->generator->update_force(it->body, duration);
    }
}

void ForceRegistry::clear()
{
    registry.clear();
}
