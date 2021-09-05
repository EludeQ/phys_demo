#include "raylib.h"

#include <vector>
#include <iostream>
#include <memory>

#include "phys/rigidbody/force_generator.h"
#include "phys/rigidbody/force_registry.h"
#include "phys/rigidbody/rigid_body.h"
#include "phys/rigidbody/gravity.h"
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
//    auto drag = std::make_shared<ParticleDrag>(5.0, 1.0);

//    EnableCursor();

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

        }

        if (IsKeyPressed(KEY_Z))
        {
            camera.target = {0.0f, 0.0f, 0.0f};
        }

        registry.update_forces(1.0f / 60.0f);

        for (auto& body : bodies)
        {
            body->integrate(1.0f / 60.0f);
            Vector3 pos{body->get_position().x, body->get_position().y, body->get_position().z};
            DrawCube(pos, 1.0f, 1.0f, 1.0f, RED);
            DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, RED);
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