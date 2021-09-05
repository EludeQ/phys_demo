//
// Created on 22/08/2021.
//

#pragma once

#include <vector>
#include <memory>

#include "force_generator.h"
#include "rigid_body.h"

class ForceRegistry
        {
        protected:
            struct Registration
                    {
                std::shared_ptr<RigidBody> body;
                std::shared_ptr<ForceGenerator> generator;
                    };

            std::vector<Registration> registry;
        public:
            // Adds rigidbody-forcegen pair.
            void add(const std::shared_ptr<RigidBody>& p_body, const std::shared_ptr<ForceGenerator>& p_fg);

            // Removes rigidbody-forcegen pair.
            void remove(const std::shared_ptr<RigidBody>& p_body, const std::shared_ptr<ForceGenerator>& p_fg);

            // Clears rigidbody-forcegen registery.
            void clear();

            // Calls all force generators to update their bodies.
            void update_forces(real duration);
        };

