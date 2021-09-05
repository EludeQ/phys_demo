//
// Created on 22/08/2021.
//

#pragma once

#include "../precision.h"

#include <memory>

class RigidBody;

class ForceGenerator
{
public:
    virtual void update_force(std::shared_ptr<RigidBody> p_body, real p_duration) = 0;
};

