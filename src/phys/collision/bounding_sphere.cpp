//
// Created on 23/08/2021.
//

#include "bounding_sphere.h"

#include <math.h>
#include <glm/gtx/norm.hpp>

BoundingSphere::BoundingSphere(const BoundingSphere &p_one, const BoundingSphere &p_two)
{
    glm::vec3 centerOffset = p_two.center - p_one.center;
    real distance = glm::length2(centerOffset);
    real radiusDiff = p_two.radius - p_one.radius;

    // Does the larger sphere enclose the small one?
    if (radiusDiff * radiusDiff >= distance)
    {
        if (p_one.radius > p_two.radius)
        {
            center = p_one.center;
            radius = p_one.radius;
        }
        else
        {
            center = p_two.center;
            radius = p_two.radius;
        }
    }
    // The two partially overlap.
    else
    {
        distance = sqrt(distance);
        radius = (distance + p_one.radius + p_two.radius) * (static_cast<real>(0.5));

        // The new center is one's center moved towards two's by an amount proportional to their radii.
        center = p_one.center;
        if (distance > 0)
        {
            center += centerOffset * ((radius - p_one.radius) / distance);
        }
    }
}

bool BoundingSphere::overlaps(const std::shared_ptr<BoundingSphere> p_other) const
{
    real distanceSquared = glm::length2(center - p_other->center);
    return distanceSquared < (radius + p_other->radius) * (radius + p_other->radius);
}
