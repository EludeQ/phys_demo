//
// Created on 23/08/2021.
//

#pragma once

#include <memory>

#include <glm/vec3.hpp>

#include "../precision.h"

struct BoundingSphere
{
    glm::vec3 center;
    real radius;
public:
    BoundingSphere(const glm::vec3 &p_center, real p_radius) : center(p_center), radius(p_radius) {}

    BoundingSphere(const BoundingSphere &p_one, const BoundingSphere &p_two);

    bool overlaps(std::shared_ptr<BoundingSphere> p_other) const;
};

