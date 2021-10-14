#include "raylib.h"
#include "raymath.h"
#include "glm/ext.hpp"

#include <vector>
#include <iostream>
#include <memory>

#include "phys/rigidbody/force_generator.h"
#include "phys/rigidbody/force_registry.h"
#include "phys/rigidbody/rigid_body.h"
#include "phys/rigidbody/gravity.h"
#include "phys/rigidbody/spring.h"
#include "phys/collision/bvh.h"

int main(void)
{
    // Raylib Init
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "Vooronderzoek Lilyphys");

    // Camera
    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 75.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_FREE);

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);

    std::vector<std::shared_ptr<RigidBody>> bodies;

    ForceRegistry registry;
    auto gravity = std::make_shared<Gravity>(glm::vec3(0.0, -20.0f, 0.0));
    std::shared_ptr<Spring> spring;
//    auto drag = std::make_shared<ParticleDrag>(5.0, 1.0);

//    EnableCursor();

    Mesh cubeMesh = GenMeshCube(1, 1, 1);
    Model cubeModel = LoadModel("../assets/material.gltf");
    Material material = cubeModel.materials[0];
//    Model cubeModel = LoadModelFromMesh(cubeMesh);

    // Game Loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateCamera(&camera);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        for (auto& body : bodies)
        {
            body->clear_accumulators();
            body->calculate_derived_data();
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            auto create_body = [&](glm::vec3 pos){ auto body = std::make_shared<RigidBody>();
                float m = 0.1f;
                float dx = 1.0f, dy = 1.0f, dz = 1.0f;
                body->set_mass(m);
                body->set_position(pos);
                body->set_damping(0.8f, 0.8f);
                glm::mat3 it;
                it[0].x = 1.0f / 12.0f * m * (pow(dy, 2.0f) + pow(dz, 2.0f));
                it[0].y = 0.0f;
                it[0].z = 0.0f;
                it[1].x = 0.0f;
                it[1].y = 1.0f / 12.0f * m * (pow(dx, 2.0f) + pow(dz, 2.0f));
                it[1].z = 0.0f;
                it[2].x = 0.0f;
                it[2].y = 0.0f;
                it[2].z = 1.0f / 12.0f * m * (pow(dx, 2.0f) + pow(dy, 2.0f));
                body->set_inertia_tensor(it);
                return body;
            };
            auto body1 = create_body(glm::vec3(0.0f, 0.0f, 0.0f));

            registry.add(body1, gravity);
            bodies.push_back(body1);

            auto body2 = create_body(glm::vec3(10.0f, 0.0f, 0.0f));
            body2->set_inverse_mass(0);
            registry.add(body2, gravity);
            bodies.push_back(body2);

            spring = std::make_shared<Spring>(glm::vec3(0.5, 0.5, 0.5f), body2, glm::vec3(0.5f, 0.5f, 0.5f), 0.1f, 2.0f);
            registry.add(body1, spring);
        }

        if (IsKeyPressed(KEY_Z))
        {
            camera.target = {0.0f, 0.0f, 0.0f};
        }

        registry.update_forces(GetFrameTime());

        for (auto& body : bodies)
        {
            body->integrate(GetFrameTime());
            Vector3 pos{body->get_position().x, body->get_position().y, body->get_position().z};
            //Vector3 ort{body->get_orientation().x, body->get_orientation().y, body->get_orientation().z};
            Quaternion ort;
            ort.x = body->get_orientation().x;
            ort.y = body->get_orientation().y;
            ort.z = body->get_orientation().z;
            ort.w = body->get_orientation().w;

            Matrix trans = MatrixMultiply(QuaternionToMatrix(ort), MatrixTranslate(body->get_position().x, body->get_position().y, body->get_position().z));
            DrawMesh(cubeMesh, material, trans);
        }

        if (spring != nullptr)
        {
            auto point1 = bodies[0]->to_global(spring->get_connection_point());
            auto point2 = bodies[1]->to_global(spring->get_other_connection_point());
            DrawLine3D(Vector3{point1.x, point1.y, point1.z}, Vector3{point2.x, point2.y, point2.z}, BLUE);
        }

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Free camera controls:", 20, 20, 10, BLACK);
        DrawText("- Hold middle mouse button and drag to pan.", 40, 40, 10, DARKGRAY);
        DrawText("- Hold Alt + Middle mouse button and drag to rotate view.", 40, 60, 10, DARKGRAY);
        DrawText("- Press Z to reset camera position.", 40, 80, 10, DARKGRAY);

        EndDrawing();
    }

    // Raylib deinit
    CloseWindow();

    return 0;
}