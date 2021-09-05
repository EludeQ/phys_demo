//
// Created on 23/08/2021.
//

#pragma once

#include <memory>
#include <vector>

#include "../rigidbody/rigid_body.h"

struct PotentialContact
{
    std::shared_ptr<RigidBody> body[2];
};

template <class BoundingVolumeClass>
class BVHNode
{
public:
    std::shared_ptr<BVHNode> children[2];

    // The bounding volume encompassing all descendants of this node.
    BoundingVolumeClass volume;

    // Only leaf nodes have a body.
    std::shared_ptr<RigidBody> body;

    bool is_leaf() const
    {
        return body != nullptr;
    }

    unsigned get_potential_contacts(std::vector<std::shared_ptr<PotentialContact>> p_contacts, unsigned p_limit) const;
    bool overlaps(std::shared_ptr<BVHNode<BoundingVolumeClass>> p_other) const;
    unsigned get_potential_contacts_with(std::shared_ptr<BVHNode<BoundingVolumeClass>> p_other, std::vector<std::shared_ptr<PotentialContact>> p_contacts, unsigned p_limit) const;
};

template <class BoundingVolumeClass>
bool BVHNode<BoundingVolumeClass>::overlaps(const std::shared_ptr<BVHNode<BoundingVolumeClass>> p_other) const
{
    return volume->overlaps(p_other->volume);
}

template <class BoundingVolumeClass>
        unsigned BVHNode<BoundingVolumeClass>::get_potential_contacts(std::vector<std::shared_ptr<PotentialContact>> p_contacts, unsigned p_limit) const
{
    if (is_leaf() || p_limit == 0)
    {
        return 0;
    }

    return children[0]->get_potential_contacts(children[1], p_contacts, p_limit);
}

template <class BoundingVolumeClass>
unsigned BVHNode<BoundingVolumeClass>::get_potential_contacts_with(const std::shared_ptr<BVHNode<BoundingVolumeClass>> p_other, std::vector<std::shared_ptr<PotentialContact>> p_contacts, unsigned p_limit) const
{
    if (!overlaps(p_other) || p_limit == 0)
    {
        return 0;
    }

    if (is_leaf() && p_other->is_leaf())
    {
        std::shared_ptr<PotentialContact> contact = std::make_shared<PotentialContact>();
        contact->body[0] = body;
        contact->body[1] = p_other->body;
        p_contacts.push_back(contact);
        return 1;
    }

    if (p_other->is_leaf() || (!is_leaf() && volume->get_size() >= p_other->volume->get_size()))
    {
        unsigned count = children[0]->get_potential_contacts_with(p_other, p_contacts, p_limit);

        if (p_limit > count)
        {
            return count + children[1]->get_potential_contacts_with(p_other, p_contacts, p_limit - count);
        }
        else
        {
            return count;
        }
    }
    else
    {
        unsigned count = get_potential_contacts_with(p_other->children[0], p_contacts, p_limit);

        if (p_limit > count)
        {
            return count + get_potential_contacts_with(p_other->children[1], p_contacts, p_limit - count);
        }
        else
        {
            return count;
        }
    }
}